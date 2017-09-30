#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

static pthread_mutex_t	mutex = NULL;
static pthread_cond_t	cond = NULL;
static unsigned int		count = 0;

/* nanosleep pthread_cond_signalの挙動がハッキリしないので作成した
   プログラム。スレッド作成前に、conditionに使用するpthread_cond_tと
   ptrehad_mutex_tの初期化を行い、通知スレッドを先に作成した。
   thread1は8秒経つまでpthread_cond_siginalは行われない

   その後、thread1からcond_signalを送信すると、一度thread2のcondition 待ちが
   解除されるはずだが、linuxでは解除されず、さらに一度解除した後、mainスレッドから
   再度解除を試みるが、linuxでは上手くいかない。

   linuxでは一度、cond_signalで通知した後、最初期化は自動で行われない、
   MacOSXの場合は元々スレッドベースの仕組みがあるが、linuxはプロセスベースの仕組みの上に
   threadの仕組みを乗せているので、threadはあくまでtempolaryのresourceであり、
   multi-threadでmessageを双方向でやり取りするRTOS的な考えて方とは異なる。
   
   帰ってから再度確認する。mutexのdeadlock/a condition valueの最初期化することで
   意図した動作になるかどうかを確認する。
*/

int main (void)
{

    int							i, rtn;
    pthread_t					th1, th2;
    int err;
	struct timespec		req, res;

	req.tv_sec  = 10;
	req.tv_nsec = 0;


	/* init mutex */
	rtn = pthread_mutex_init(&mutex, NULL);
	if (rtn != 0) {
		fprintf(stderr, "pthread_mutex_init() failed for %d.\n", rtn);
		exit(EXIT_FAILURE);
	}


	/* init cond */
	rtn = pthread_cond_init(&cond, NULL);
	if (rtn != 0) {
		fprintf(stderr, "pthread_cond_init() failed for %d.\n", rtn);
		exit(EXIT_FAILURE);
	}

	/* create threads */
	rtn = pthread_create(&th1, NULL, thread1, (void *)NULL);
	if (rtn != 0) {
		fprintf(stderr, "pthread_create() - thread#1 failed for %d.\n", rtn);
		exit(EXIT_FAILURE);
	}


	/* create threads */
	rtn = pthread_create(&th2, NULL, thread2, (void *)NULL);
	if (rtn != 0) {
		fprintf(stderr, "pthread_create() - thread#2 failed for %d.\n", rtn);
		exit(EXIT_FAILURE);
	}

	//	nanosleep(&req,&res);


	/* join */

	pthread_join(th1, NULL);
#if 0　//  2回目の通知
	pthread_cond_signal(&cond);
#endif
	// 強制canel
	pthread_cancel(th2);
  err = pthread_join(th2, NULL);

	err = pthread_cond_destroy(&cond);
	printf("pthread_cond_destory %d\n",err);
	err = pthread_mutex_destroy(&mutex);
	printf("pthread_mutex_destroy %d\n",err);

    exit(EXIT_SUCCESS);

}


void *thread1(void *dummy)
{

	int					ret;
	struct timespec		req, res;

	req.tv_sec  = 1;
	req.tv_nsec = 0;

	while(1) {

		putchar('0');

		pthread_mutex_lock(&mutex);
		count++;
		pthread_mutex_unlock(&mutex);

		if (count == 8){
			pthread_cond_signal(&cond);
			break;
		}
		ret = nanosleep(&req, &res);
		while (ret != 0 && errno == EINTR)
			ret = nanosleep(&req, &res);

		if (ret != 0) {
			perror("nanosleep()");
			return (void *) NULL;
		}

		fflush(stdout);
	}

	pthread_exit(0);
	return (void *) NULL;

}


void *thread2(void *dummy)
{

	struct timespec		req;

	req.tv_sec  = 0;
	req.tv_nsec = 10*1000*1000;

  pthread_cleanup_push(pthread_mutex_unlock,&mutex);

	while (1) {

//	putchar('1');

		pthread_mutex_lock(&mutex);
		pthread_cond_timedwait(&cond, &mutex,&req);
		pthread_mutex_unlock(&mutex);
//		break;
		
//	putchar('4');

	}

	pthread_cleanup_pop(0);

  pthread_exit(0);
  return (void *) NULL;
}
