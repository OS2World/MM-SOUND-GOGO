/*
 *   part of this code is origined from
 *   GOGO-no-coda
 *
 *   Copyright(C) 2001,2002,2003 gogo-developer
 */

#ifndef THREAD_H_
#define THREAD_H_

/* �v���b�g�z�[����ˑ� */

typedef void* (*gogo_thread_func)(void *); 

/*
 *	�}���`�X���b�h�ɑΉ�����ꍇ�́A
 *	���̃v���b�g�z�[���ɍ��킹�Ĉȉ��̌^�Ɗ֐��܂��̓}�N����p�ӂ��邱��
 *
 *	�v���b�g�z�[���ˑ��̌^ 
 *
 *	gogo_thread	�X���b�h�����i�[����^
 *	gogo_mutex	�~���[�e�b�N�X�����i�[����^
 *  gogo_semaphore �Z�}�t�H�����i�[����^
 *
 *	�v���b�g�z�[���ˑ��̊֐��܂��̓}�N�� 
 *	int ��Ԃ��֐��͐���I���� 0 ��Ԃ��A�ُ�I���Ŕ� 0 ��Ԃ����ƁB
 *
 *	�X���b�h�֌W�̏������B���̃X���b�h�֌W�֐����g���O�Ɉ�x�����Ă΂��B
 *	int gogo_initialize_thread_unit(void)
 *
 *	�X���b�h�֌W�̏I�������B��x�����Ă΂��B������Ă񂾌�A���̃X���b�h�֐��Q���Ă�ł͂����Ȃ��B
 *	int gogo_finalize_thread_unit(void)
 *
 *	�X���b�h�𐶐�����B
 *	int gogo_create_thread(gogo_thread* pthread, gogo_thread_func func, void *data)
 *
 *	�X���b�h�̏I����҂B
 *	int gogo_join_thread(gogo_thread* pthread)
 *
 *	�X���b�h��j������B�j������O�ɏI����҂��ƁB
 *	int gogo_destroy_thread(gogo_thread* pthread)
 *
 *	�~���[�e�b�N�X�𐶐�����B
 *	�ċA�~���[�e�b�N�X���ǂ����̓v���b�g�z�[���ˑ��Ȃ̂ŁA�ċA���ǂ����Ɉˑ����Ȃ��悤�Ɏg�����ƁB
 *	int gogo_create_mutex(gogo_mutex* pmutex)
 *
 *	�~���[�e�b�N�X��j������B
 *	int gogo_destroy_mutex(gogo_mutex* pmutex)
 *
 *	�~���[�e�b�N�X���l������B�l������ł���܂ŉi���ɑ҂B
 *	int gogo_lock_mutex(gogo_mutex* pmutex)
 *
 *	�~���[�e�b�N�X���������B
 *	int gogo_unlock_mutex(gogo_mutex* pmutex)
 *
 *	�Z�}�t�H�𐶐�����B
 *	�����l0��2�l�Z�}�t�H�B
 *  int gogo_create_semaphore(gogo_semaphore* pSemaphore)
 *
 *	�Z�}�t�H��j������B
 *  int gogo_destroy_semaphore(gogo_semaphore* pSemaphore)
 *
 *	�Z�}�t�H���l������B�l������ł���܂ŉi���ɑ҂B
 *  int gogo_lock_semaphore(gogo_semaphore* pSemaphore)
 *
 *	�Z�}�t�H���������B
 *  int gogo_unlock_semaphore(gogo_semaphore* pSemaphore)
 *
 *	�Z�}�t�H���l������B�l���ł���܂� timeout �~���b�҂B
 *  �l���ł����� 0 ��Ԃ��B�G���[�܂��� timeout ������A��0��Ԃ��B
 *  int gogo_trylocktimeout_semaphore(gogo_semaphore* pSemaphore, int timeout)
 *
 *	���̃X���b�h�Ɏ��s����^����B
 *  void gogo_yield_thread()						
 *
 *	CPU �̐��� *pCPUs �ɁA��������X���b�h���� *pTHREADs �ɕԂ��B
 *	�킩��Ȃ��ꍇ�͗����K��1�ɂ��邱�ƁB
 *	int gogo_get_cpu_count(int *pCPUs, int *pTHREADs)
 *
 *	�X���b�h���[�J���f�[�^�\���̂ɒu�������ϐ�������΁A
 *	�L���萔 GOGO_THREAD_VARIABLES �ɒ�`���Ă��������B
 *
 */

#define	MT_ENCODER

#if		defined(USE_WINTHREAD)
#  include	"../win/thread_win.h"
#elif	defined(USE_PTHREAD)
#  include	"../pthread/thread_pthread.h"
#elif defined(USE_BTHREAD)
#  include	"../be/thread_be.h"
#elif defined(USE_OS2THREAD)
#  include	"../os2/thread_os2.h"
#elif defined(USE_RFORK)
#  include	"../rfork/thread_rfork.h"
#else
#  undef	MT_ENCODER
#  define	ST_ENCODER
#  define	gogo_get_cpu_count(pCPU,pTHREADs) ((*(pCPU)=1),(*(pTHREADs)=1),0)
#endif

typedef unsigned int uint32;

/**
 * �v���b�g�z�[����ˑ����[�J���ϐ�
 */
typedef struct gogo_thread_data_s {
/* �v���b�g�z�[����ˑ����[�J���ϐ� */
	float	mfbuf[2][4][576];	/* ->FFT, ->PFB */

  /* variables for newmdct.c */
        float	(*sb[4])[18][SBLIMIT];
        float	sb_sample[3][2][18][SBLIMIT];  /* PFB -> MDCT */

        float	xr[2][2][576];         /* MDCT -> Non-Linear Quantization  */
	uint32	xr_sign[2][2][576];

        float	xrpow[2][2][576];      /* Non-Linear Quantization -> Iteration Loop */
	float	work_xrpow[576]; //, save_xrpow[576], best_xrpow[576];	/* quantize.c */
        float	xrpow_sum[2][2];
        float	xrpow_max[2][2];

	int	l3_enc[2][2][576];
	III_scalefac_t	scalefac[2][2];

	int	ath_over[2][2];		/* calc_xmin() -> calc_noise() */
	III_psy_xmin	l3_xmin[2][2];	/* calc_xmin() -> calc_noise() */

	/* fft and energy calculation    */
        float	wsamp_L[2 /*granule*/][2 /*channel*/][BLKSIZE];     /* fft() -> L3psycho_anal() */
        float	wsamp_S[2 /*granule*/][2 /*channel*/][3][BLKSIZE_s];/* fft() -> L3psycho_anal() */
/* BLKSIZE=1024, BLKSIZE_s = 256 => max(BLKSIZE,BLKSIZE_s*3) = 1024 */
//		float	psywork[BLKSIZE*4];		/* wsampl_{L,S} 4��(energy�Ƌ��p�����ق����悢��?) */
		float	psywork[576*2*4*4];		/* FFT�ł�work(576*2*4*4*4byte)�Ƃ��Ďg�� */
		                                /* �������d�Ȃ�Ȃ� quantize.c �� distort �ł����p���Ďg�� */
        float	energy[HBLKSIZE*4];              /* �̈��4�{�ɂ����FFT��ɂ܂Ƃ߂ď����\ */
        float	energy_s[3][HBLKSIZE_s*4];       /* �̈��4�{�ɂ����FFT��ɂ܂Ƃ߂ď����\ */

	/* psycho acoustics */
	float	tot_ener[4];	/* private copy of RW.tot_ener */
	III_side_info_t	l3_side;

/* �v���b�g�z�[���ˑ��X���b�h���[�J���ϐ� */
#ifdef GOGO_THREAD_VARIABLES
	GOGO_THREAD_VARIABLES;
#endif

/* �A���C�����g�֌W�Ȃ����̂͂������牺�� */
	struct gogo_thread_data_s	*next;
	void	*unaligned;
	int	tid;

	int	padding;		  /* padding for the current frame? */
	int	mode_ext;

	int	bitrate_index;
	int	ResvSize;

	// WMP6.4�Ή��̂��� ancillary ������� part2_3_length ��ǉ����Ă���̂�����
	// ���̒ǉ�����r�b�g��
	int additional_part2_3_length[2 /*granule*/][2 /*channel*/]; 

#ifdef	MT_ENCODER
	int	exit_status;
	gogo_thread	thread;
	gogo_mutex	*critical_region;
#endif
} gogo_thread_data;	// <- gogo2��encodeframe_arg_t����

#endif // THREAD_H_

