
2001 Oct. 9

fixu32.c alignes variables to 16bytes for SSE insted of BCC-linker,
which is programmed by Sava.

usage:
	fixu32 [-u] [-c] [-padding16] [-padding32] [-v] objfile [output_objfile]
	   -u   	Update objfile
	   -c   	validate Checksum
	   -padding16	force segment length aligned by 16bytes
	   -padding32	                     aligned by 32bytes
	   -v   	Verbose mode


���̃v���O������16byte alignment�̐ݒ肪�ł��Ȃ�BCC�ɑ�����
obj�������I�ɏ��������邱�Ƃ�SSE�ɑΉ�������v���O�����ł��B
���쌠�� ���� ����ɂ���܂��B

����񍐂͂���܂����A��ؖ��ۏ؂ł��̂Ŏ��Ȃ̐ӔC�ɂ����ė��p���Ă��������B
