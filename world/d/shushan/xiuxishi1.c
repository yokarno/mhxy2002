// xiuxishi.c by yushu.2000.11
inherit ROOM;
#include <ansi.h>

void create()
{
	set("short",HIR "��" HIY "����" HIR "��" NOR);
	set("long", @LONG

��������ɽ���ڵ���Ϣ�ң������е��ɣ����Ǵ�ɨ�ķǳ��ɾ���һ��
���̿�ǽ���ţ������ȥҲ��һ����Ϣ�ң����ϵ����˽�����Ϣ���Ѻ�
��ȥ�������ĵ��Ҹ�����˯��������
LONG
	);
        set("exits", ([
	         "west" : __DIR__"xiuxishi",
	  ]));

       set("sleep_room",1);  
       setup();
	replace_program(ROOM);
}
