/* 
   X�Ǥ��̿�����ǡ����䥿���פ�̾�����դ��ƶ��̤��ޤ�
   �ºݤˤϤ���̾�����б����������ͤ�Ȥ��ޤ�������
   �����ͤ�֥��ȥ�פȸƤӤޤ� 
*/
/*
  Atom XInternAtom(Display *display,char *atom_name,Bool only_if_exists);
  ���˥��ȥब����Ƥ���,atom_name���б����륢�ȥब�Τꤿ�����ˤ�
  only_if_exists��True�򿷤������ȥ������������ˤ�False�����

  char *XGetAtomName(Display *display,Atom atom)
  atom���б�����ʸ��������ޤ�
*/
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>

main()
{
  Display *display;
  Atom atom;
  display = XOpenDisplay(NULL);

  /* XA_CUT_BUFFER0�ϴ�������ѤߤΥ��ȥ� */
  printf("Cut buffer 0: %s\n", XGetAtomName(display,XA_CUT_BUFFER0));
  /* True�ʤΤǿ��������ȥ����������ʤ� */
  atom = XInternAtom(display,"My String", True);
  printf("Atom for custom string: %d\n",atom);
  /* False�ʤΤǿ��������ȥब��������� */
  atom = XInternAtom(display,"My String",False);
  printf("Atom for custom string: %d\n",atom);

  printf("Custom string: %s\n", XGetAtomName(display,atom));
}