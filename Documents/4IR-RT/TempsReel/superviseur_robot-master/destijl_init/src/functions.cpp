#include "../header/functions.h"

char mode_start;

void write_in_queue(RT_QUEUE *, MessageToMon);

void f_server(void *arg) {
    int err;
    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);

    err = run_nodejs("/usr/local/bin/node", "/home/pi/Interface_Robot/server.js");

    if (err < 0) {
        printf("Failed to start nodejs: %s\n", strerror(-err));
        exit(EXIT_FAILURE);
    } else {
#ifdef _WITH_TRACE_
        printf("%s: nodejs started\n", info.name);
#endif
        open_server();
        rt_sem_broadcast(&sem_serverOk);
    }
}

void f_sendToMon(void * arg) {
    int err;
    MessageToMon msg;

    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);

#ifdef _WITH_TRACE_
    printf("%s : waiting for sem_serverOk\n", info.name);
#endif
    rt_sem_p(&sem_serverOk, TM_INFINITE);
    while (1) {
        
        /* Implémentation de la fonctionnalité 6 : Traitement de la perte de communication */
        rt_mutex_acquire(&mutex_communicationPerdue, TM_INFINITE);
        if(communicationPerdue){
            rt_mutex_release(&mutex_communicationPerdue);
            while(1){}
        }
        rt_mutex_release(&mutex_communicationPerdue);
        

#ifdef _WITH_TRACE_
        printf("%s : waiting for a message in queue\n", info.name);
#endif
        if (rt_queue_read(&q_messageToMon, &msg, sizeof (MessageToRobot), TM_INFINITE) >= 0) {
#ifdef _WITH_TRACE_
            printf("%s : message {%s,%s} in queue\n", info.name, msg.header, msg.data);
#endif
            /* Implémentation de la fonctionnalité 5 : Détection de perte de communication */
            if(send_message_to_monitor(msg.header, msg.data) == 0) {
                free_msgToMon_data(&msg);
                rt_queue_free(&q_messageToMon, &msg);
            } else {
                rt_sem_broadcast(&sem_communicationLost);
            }
        } else {
            printf("Error msg queue write: %s\n", strerror(-err));
        }
    }
}

void f_receiveFromMon(void *arg) {
    MessageFromMon msg;
    int err;

    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);
    
    /* Implémentation de la fonctionnalité 6 : Traitement de la perte de communication */
    rt_mutex_acquire(&mutex_communicationPerdue, TM_INFINITE);
    if(communicationPerdue){
        rt_mutex_release(&mutex_communicationPerdue);
        while(1){}
    }
    rt_mutex_release(&mutex_communicationPerdue);
    
#ifdef _WITH_TRACE_
    printf("%s : waiting for sem_serverOk\n", info.name);
#endif
    rt_sem_p(&sem_serverOk, TM_INFINITE);
    do {
#ifdef _WITH_TRACE_
        printf("%s : waiting for a message from monitor\n", info.name);
#endif
        /* Implémentation de la fonctionnalité 5 : Détection de la perte de communication */
        if(receive_message_from_monitor(msg.header, msg.data) == 0){
       
#ifdef _WITH_TRACE_
        printf("%s: msg {header:%s,data=%s} received from UI\n", info.name, msg.header, msg.data);
#endif
            if (strcmp(msg.header, HEADER_MTS_COM_DMB) == 0) {
                 if (msg.data[0] == OPEN_COM_DMB) { // Open communication supervisor-robot
#ifdef _WITH_TRACE_
                printf("%s: message open Xbee communication\n", info.name);
#endif
                    rt_sem_v(&sem_openComRobot);
                }
            } else if (strcmp(msg.header, HEADER_MTS_DMB_ORDER) == 0) {
                if (msg.data[0] == DMB_START_WITHOUT_WD) { // Start robot without watchdog
#ifdef _WITH_TRACE_
                printf("%s: message start robot\n", info.name);
#endif 
                    rt_sem_v(&sem_startRobot);
                } else if (msg.data[0] == DMB_START_WITH_WD) { // Start robot with watchdog
                    rt_mutex_acquire(&mutex_watchdog, TM_INFINITE);
                    watchdog = true;    
                    rt_mutex_release(&mutex_watchdog);
                               

                } else if ((msg.data[0] == DMB_GO_BACK)
                        || (msg.data[0] == DMB_GO_FORWARD)
                        || (msg.data[0] == DMB_GO_LEFT)
                        || (msg.data[0] == DMB_GO_RIGHT)
                        || (msg.data[0] == DMB_STOP_MOVE)) {

                    rt_mutex_acquire(&mutex_move, TM_INFINITE);
                    move = msg.data[0];
                    rt_mutex_release(&mutex_move);
#ifdef _WITH_TRACE_
                printf("%s: message update movement with %c\n", info.name, move);
#endif

                }
            }
        } else {
            rt_sem_broadcast(&sem_communicationLost);
        }
            

}

void f_openComRobot(void * arg) {
    int err;

    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);

    while (1) {
#ifdef _WITH_TRACE_
        printf("%s : Wait sem_openComRobot\n", info.name);
#endif
        rt_sem_p(&sem_openComRobot, TM_INFINITE);
#ifdef _WITH_TRACE_
        printf("%s : sem_openComRobot arrived => open communication robot\n", info.name);
#endif
        /* Implémentation de la fonctionnalité 6 : Traitement de la perte de communication */
        rt_mutex_acquire(&mutex_communicationPerdue, TM_INFINITE);
        if(communicationPerdue){
            rt_mutex_release(&mutex_communicationPerdue);
            while(1){}
        }
        rt_mutex_release(&mutex_communicationPerdue);
        
        err = open_communication_robot();
        if (err == 0) {
#ifdef _WITH_TRACE_
            printf("%s : the communication is opened\n", info.name);
#endif
            MessageToMon msg;
            set_msgToMon_header(&msg, HEADER_STM_ACK);
            write_in_queue(&q_messageToMon, msg);
        } else {
            MessageToMon msg;
            set_msgToMon_header(&msg, HEADER_STM_NO_ACK);
            write_in_queue(&q_messageToMon, msg);
        }
    }
}

void f_startRobot(void * arg) {
    int err;
    bool watchdogLoc;
    bool commandPasTransmise = true;
    
    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);
    

    while (1) {
#ifdef _WITH_TRACE_
        printf("%s : Wait sem_startRobot\n", info.name);
#endif
        rt_sem_p(&sem_startRobot, TM_INFINITE);
        
        /* Implémentation de la fonctionnalité 6 : Traitement de la perte de communication */
        rt_mutex_acquire(&mutex_communicationPerdue, TM_INFINITE);
        if(communicationPerdue){
            rt_mutex_release(&mutex_communicationPerdue);
            while(1){}
        }
        rt_mutex_release(&mutex_communicationPerdue);
        
#ifdef _WITH_TRACE_
        printf("%s : sem_startRobot arrived => Start robot\n", info.name);
#endif
        
        /* Implémentation fonctionnalité 10 : Démarrage du WatchDog*/
        rt_mutex_acquire(&mutex_watchdog, TM_INFINITE);
        watchdogLoc = watchdog;
        rt_mutex_release(&mutex_watchdog);
        
        
        while(commandPasTransmise){
            err = send_command_to_robot(DMB_START_WITHOUT_WD);
            
            if(err == 0){
#ifdef _WITH_TRACE_
    printf("%s : the robot is started\n", info.name);
#endif
                rt_mutex_acquire(&mutex_robotStarted, TM_INFINITE);
                robotStarted = 1;
                rt_mutex_release(&mutex_robotStarted);
                MessageToMon msg;
                set_msgToMon_header(&msg, HEADER_STM_ACK);
                write_in_queue(&q_messageToMon, msg);
                commandPasTransmise = false;
                
                // Remise à 0 du compteur lorsqu'une communication est réussie
                rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);      
                compteurPerte = 0;
                rt_mutex_release(&mutex_compteurPerte);
                
                
            }
            else{
                rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);      
                compteurPerte++;
                if(compteurPerte > 3){
                    rt_sem_broadcast(&sem_robotLost);
                    MessageToMon msg;
                    set_msgToMon_header(&msg, HEADER_STM_NO_ACK);
                    write_in_queue(&q_messageToMon, msg);
                    commandPasTransmise = false; // Pour sortir de la boucle
                }
                rt_mutex_release(&mutex_compteurPerte);
                
            }
        }
    }
}

void f_move(void *arg) {
    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);

    char err;
    bool commandeErr=false;
    
    /* PERIODIC START */
#ifdef _WITH_TRACE_
    printf("%s: start period\n", info.name);
#endif
    rt_task_set_periodic(NULL, TM_NOW, 100000000);
    while (1) {
#ifdef _WITH_TRACE_
        printf("%s: Wait period \n", info.name);
#endif
        rt_task_wait_period(NULL);
#ifdef _WITH_TRACE_
        printf("%s: Periodic activation\n", info.name);
        printf("%s: move equals %c\n", info.name, move);
#endif
        rt_mutex_acquire(&mutex_robotStarted, TM_INFINITE);
        if (robotStarted) {
            
            rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);
            
            if (compteurPerte<3 && commandeErr==false){
            
                rt_mutex_release(&mutex_compteurPerte);
                rt_mutex_acquire(&mutex_move, TM_INFINITE);
                err=send_command_to_robot(move);
                rt_mutex_release(&mutex_move);
                commandeErr=false;
#ifdef _WITH_TRACE_
            printf("%s: the movement %c was sent\n", info.name, move);
#endif
                if (err!=ROBOT_OK){
                            commandeErr=true;
                            rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);
                            compteurPerte ++;
                            rt_mutex_release(&mutex_compteurPerte);
                        }
            }
        }
        else{
            rt_mutex_release(&mutex_robotStarted);
            while(1)
            
        }
        rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);
        compteurPerte =0;
        rt_mutex_release(&mutex_compteurPerte);
        rt_mutex_release(&mutex_robotStarted);
    }
}

void write_in_queue(RT_QUEUE *queue, MessageToMon msg) {
    void *buff;
    buff = rt_queue_alloc(&q_messageToMon, sizeof (MessageToMon));
    memcpy(buff, &msg, sizeof (MessageToMon));
    rt_queue_send(&q_messageToMon, buff, sizeof (MessageToMon), Q_NORMAL);
}

void f_battery(void *arg){
    
    char batLevel;
    char err;
    bool commandeErr=false;
    /* INIT */
    RT_TASK_INFO info;
    rt_task_inquire(NULL, &info);
    printf("Init %s\n", info.name);
    rt_sem_p(&sem_barrier, TM_INFINITE);
    
     /* PERIODIC START */
#ifdef _WITH_TRACE_
    printf("%s: start period\n", info.name);
#endif
    rt_task_set_periodic(NULL, TM_NOW, 500000000);
    while (1) {
#ifdef _WITH_TRACE_
        printf("%s: Wait period \n", info.name);
#endif
        rt_task_wait_period(NULL);
#ifdef _WITH_TRACE_
        printf("%s: Periodic activation\n", info.name);
        printf("%s: move equals %c\n", info.name, move);
#endif
#ifdef _WITH_TRACE_
            printf("%s : the robot is started\n", info.name);
#endif
        rt_mutex_acquire(&mutex_robotStarted, TM_INFINITE);
        if (robotStarted) {          
            rt_mutex_acquire(&mutex_communicationPerdue, TM_INFINITE);
            
            if(communicationPerdue){
                rt_mutex_release(&mutex_communicationPerdue);
                rt_mutex_release(&mutex_robotStarted);
                while(1)
            }
            rt_mutex_release(&mutex_communicationPerdue);
            rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);
                if (compteurPerte<3 && commandeErr==false){
                    rt_mutex_release(&mutex_compteurPerte);
                    err=send_command_to_robot(DMB_GET_VBAT,&batLevel);
                    if (err!=ROBOT_OK){
                        commandeErr=true;
                        rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);
                        compteurPerte ++;
                        rt_mutex_release(&mutex_compteurPerte);
                    }
                
                    else{
                        commandeErr=false;
                        rt_mutex_acquire(&mutex_compteurPerte, TM_INFINITE);
                        compteurPerte=0;
                        rt_mutex_release(&mutex_compteurPerte);
                   
                        MessageToMon msg;
                        set_msgToMon_header(&msg, HEADER_STM_BAT);
                        set_msgToMon_data(&msg,&batLevel);
                        write_in_queue(&q_messageToMon, msg);
                    }
                    
                }
            
            
            rt_sem_broadcast(&sem_robotLost);
            rt_mutex_release(&mutex_robotStarted);
            
    }
}