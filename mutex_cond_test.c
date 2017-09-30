#define _XOPEN_SOURCE 600

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>

static pthread_mutex_t	mutex = NULL;
static pthread_cond_t	cond = NULL;
static unsigned int		count = 0;

/* nanosleep pthread_cond_signal�̋������n�b�L�����Ȃ��̂ō쐬����
   �v���O�����B�X���b�h�쐬�O�ɁAcondition�Ɏg�p����pthread_cond_t��
   ptrehad_mutex_t�̏��������s���A�ʒm�X���b�h���ɍ쐬�����B
   thread1��8�b�o�܂�pthread_cond_siginal�͍s���Ȃ�

   ���̌�Athread1����cond_signal�𑗐M����ƁA��xthread2��condition �҂���
   ���������͂������Alinux�ł͉������ꂸ�A����Ɉ�x����������Amain�X���b�h����
   �ēx���������݂邪�Alinux�ł͏�肭�����Ȃ��B

   linux�ł͈�x�Acond_signal�Œʒm������A�ŏ������͎����ōs���Ȃ��A
   MacOSX�̏ꍇ�͌��X�X���b�h�x�[�X�̎d�g�݂����邪�Alinux�̓v���Z�X�x�[�X�̎d�g�݂̏��
   thread�̎d�g�݂��悹�Ă���̂ŁAthread�͂����܂�tempolary��resource�ł���A
   multi-thread��message��o�����ł���肷��RTOS�I�ȍl���ĕ��Ƃ͈قȂ�B
   
   �A���Ă���ēx�m�F����Bmutex��deadlock/a condition value�̍ŏ��������邱�Ƃ�
   �Ӑ}��������ɂȂ邩�ǂ������m�F����B
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
#if 0�@//  2��ڂ̒ʒm
	pthread_cond_signal(&cond);
#endif
	// ����canel
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
