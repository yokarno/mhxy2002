//renshenguo-yuan.c

inherit ROOM;

void create ()
{
	set ("short", "�˲ι�԰");
	set ("long", @LONG

�ô��һ���˲ι�԰���޴�Ĺ����ϵ���һöö���˴������ε�
�˲ι���ֻ�ǲ�֪����������Ū����������˵���˲ι������ޱȣ�
Ҫ����ժһ��ʲô���Բ��ϡ�
LONG);

	set("exits", 
	([ //sizeof() == 4
	]));
	
	set("objects", 
	([ //sizeof() == 1
	]));
       set("alternative_die",1);
	set("outdoors", "wuzhuang");

	setup();
}

void init()
{
	object me, zhenyuan;

	me = this_player();

	if( me->query_temp("used_huangtong_key") == 1 )
	{
		me->delete_temp("used_huangtong_key");
		
		message_vision("ֻ������������Ц����Ԫ�������˳�����\n", me);
		message_vision("��Ԫ����˵������Ȼ���㷢���ˡ������ǾͿ����˲ι����ɣ�\n\n\n", me);

		if( !objectp(zhenyuan=present("zhenyuan daxian", environment(me))) )
		{//if zhenyuan already here, we do not need creat another one.
			zhenyuan = new(__DIR__"npc/zhenyuan");
			zhenyuan->move(environment(me));
		}
		zhenyuan->start_renshen();
	}
}

void alternative_die(object me)
{
       object who=this_object();
      	string here = (string)environment(me);
	string there = who->query_temp("wzg/from");

       message_vision("��Ԫ���ɶ���$N̾��һ����,ҡ��ҡͷ��\n",me);
            there = "/d/city/kezhan";
       me->set_temp("accept",0);
	message_vision("��Ԫ���ɵĴ��䳯��$N����һ�֡�\n",me);
	me->move(there);
      if ((int)me->query("kee") < 1) me->set("kee",0);
      if ((int)me->query("sen") < 1) me->set("sen",0);
      if ((int)me->query("eff_sen") < 1) me->set("eff_sen",100);
      if ((int)me->query("eff_kee") < 1) me->set("eff_kee",100);
	message_vision("���������һֻ�޴����������һ����ֻ��$N�����滬�˳�����\n",me);
	return ;
}
          