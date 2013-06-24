/*
 *   part of this code is origined from
 *   GOGO-no-coda
 *
 *   Copyright(C) 2001,2002,2003 gogo-developer
 */

/*
 *	����� engine\thread.h ���� #include �����t�@�C���ł��B
 *	���̃t�@�C�����璼�� #include ����Ȃ����Ƃ�z�肵�Ă��܂��B
 *	This file can be included by only engine/thread.h.
 */

#include <pthread.h>
#include <semaphore.h>

#include "common.h"

typedef	pthread_t       gogo_thread;
typedef pthread_mutex_t gogo_mutex;
typedef sem_t		gogo_semaphore;

BEGIN_C_DECLS
int gogo_initialize_thread_unit(void);
#define gogo_finalize_thread_unit()		(0)
int gogo_create_thread(gogo_thread* pThread, gogo_thread_func func, void *data);
#define	gogo_join_thread(pThread)		pthread_join(*(pThread), NULL)
#define	gogo_destroy_thread(pThread)		(0)			
#define	gogo_yield_thread()			(sched_yield())

#define	gogo_create_mutex(pMutex)	((*(pMutex) = (gogo_mutex)PTHREAD_MUTEX_INITIALIZER), 0)
#define	gogo_destroy_mutex(pMutex)	(0)
#define	gogo_lock_mutex(pMutex)		pthread_mutex_lock(pMutex)
#define	gogo_unlock_mutex(pMutex)	pthread_mutex_unlock(pMutex)

#define	gogo_create_semaphore(pSemaphore)	sem_init(pSemaphore,0,1)
#define	gogo_destroy_semaphore(pSemaphore)	sem_destroy(pSemaphore)
#define	gogo_lock_semaphore(pSemaphore)		sem_wait(pSemaphore)
#define	gogo_unlock_semaphore(pSemaphore)	sem_post(pSemaphore)
// ����� Linux �R�[�h�� gogo_trylocktimeout_semaphore ���g���Ă��Ȃ��̂Ŏ�𔲂��܂����Ă���D
// �g���ꍇ�͂����ƒ����܂��D
#define	gogo_trylocktimeout_semaphore(pSemaphore, timeout) \
		(sem_trywait(pSemaphore) == 0 ? 0 : usleep(timeout*1000), sem_trywait(pSemaphore))

int gogo_get_cpu_count(int *pCPUs, int *nTHERADs);
END_C_DECLS

