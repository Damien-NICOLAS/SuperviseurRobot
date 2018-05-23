/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   functions.h
 * Author: pehladik
 *
 * Created on 15 janvier 2018, 12:50
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <alchemy/task.h>
#include <alchemy/timer.h>
#include <alchemy/mutex.h>
#include <alchemy/sem.h>
#include <alchemy/queue.h>

#include "../../src/monitor.h"    
#include "../../src/robot.h"
#include "../../src/image.h"
#include "../../src/message.h"

extern RT_TASK th_server;
extern RT_TASK th_sendToMon;
extern RT_TASK th_receiveFromMon;
extern RT_TASK th_openComRobot;
extern RT_TASK th_startRobot;
extern RT_TASK th_move;

//Thread Robot :
extern RT_TASK th_refreshWD;
extern RT_TASK th_battery;
extern RT_TASK th_repriseComm;
extern RT_TASK th_perteRobot;

extern RT_MUTEX mutex_robotStarted;
extern RT_MUTEX mutex_move;

//Mutex Robot :
extern RT_MUTEX mutex_watchdog;
extern RT_MUTEX mutex_communicationPerdue;
extern RT_MUTEX mutex_compteurPerte;
//Mutex Arene :
extern RT_MUTEX mutex_camOpen;


extern RT_SEM sem_barrier;
extern RT_SEM sem_openComRobot;
extern RT_SEM sem_serverOk;
extern RT_SEM sem_startRobot;

//Semaphore Robot :
extern RT_SEM sem_communicationPerdue;
extern RT_SEM sem_startWD;
extern RT_SEM sem_robotLost;

extern RT_QUEUE q_messageToMon;

extern int etatCommMoniteur;
extern int robotStarted;
extern char move;

//Shared Variable Robot :
extern bool watchdog;
extern bool communicationPerdue;
extern int compteurPerte;
//Shared Variable Arene :
extern bool camOpen;

extern int MSG_QUEUE_SIZE;

extern int PRIORITY_TSERVER;
extern int PRIORITY_TOPENCOMROBOT;
extern int PRIORITY_TMOVE;
extern int PRIORITY_TSENDTOMON;
extern int PRIORITY_TRECEIVEFROMMON;
extern int PRIORITY_TSTARTROBOT;

//Priority Robot :
extern int PRIORITY_TREFRESHWD;
extern int PRIORITY_TBATTERY;
extern int PRIORITY_TREPRISECOMM;
extern int PRIORITY_TPERTEROBOT;


void f_server(void *arg);
void f_sendToMon(void *arg);
void f_receiveFromMon(void *arg);
void f_openComRobot(void * arg);
void f_move(void *arg);
void f_startRobot(void *arg);

//Fonction Robot :
void f_refreshWD(void *arg);
void f_battery(void *arg);
void f_repriseComm(void *arg);
void f_perteRobot(void *arg);

#endif /* FUNCTIONS_H */

