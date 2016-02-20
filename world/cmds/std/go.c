// go.c
#include <ansi.h>
inherit F_CLEAN_UP;
#include "/cmds/std/valid_move.h";

mapping default_dirs = ([
	"north":		"��",
	"south":		"��",
	"east":			"��",
	"west":			"��",
	"northup":		"����",
	"southup":		"�ϱ�",
	"eastup":		"����",
	"westup":		"����",
	"northdown":	"����",
	"southdown":	"�ϱ�",
	"eastdown":		"����",
	"westdown":		"����",
	"northeast":	"����",
	"northwest":	"����",
	"southeast":	"����",
	"southwest":	"����",
	"up":			"��",
	"down":			"��",
	"out":			"��",
	"enter":		"��",
	"left": 		"��",
	"right":		"��",
]);
static  mapping empty_mapping = ([ ]);

void create() { seteuid(getuid()); }

// follow will have silent=2, so as to reduce the CPU load.
int main(object me, string arg, int silent)
{
    	mixed dest;
	string ridemsg, mout, min, dir,msg, thing_msg;
	object env, obj, ridee,thing;
	mapping exit;
	int valid;
       mapping my, my_temp;
       mapping my_env, my_armor;

	if( !arg ) return notify_fail("��Ҫ���ĸ������ߣ�\n");

        if(!valid_move(me)) return 0;

	env = environment(me);
	if(!env) return notify_fail("������Ҳȥ���ˡ�\n");

	if( !mapp(exit = env->query("exits")) || !exit[arg] ||  undefinedp(exit[arg]) ) {
		if( query_verb()=="go")
			return notify_fail("�������û�г�·��\n");
		else
			return 0;
	}
	dest = exit[arg];

        my = me->query_entire_dbase();
        my_temp = me->query_entire_temp_dbase();
        if (! my_temp) my_temp = empty_mapping;

        my_armor = my_temp["armor"];
        if (! my_armor) my_armor = empty_mapping;

        my_env = my["env"];
        if (! my_env) my_env = empty_mapping;

	if (dest && objectp(dest))
	    obj = dest;
	else if( !(obj = load_object(dest)) )
	        return notify_fail("��Ҫȥ������û����ͨ��\n");
	else if( !(obj = find_object(dest)) )
		return notify_fail("�޷��ƶ���\n");

	valid=(int)env->valid_leave(me, arg);
	if( !valid ) return 0;
	if(valid>1) return 1;

	if( !undefinedp(default_dirs[arg]) )
		dir = default_dirs[arg];
	else
		dir = arg;

        // snowcat 12/20/97
        if (ridee = me->ride())
          ridemsg = ridee->query("ride/msg")+"��"+ridee->name();
        else  
          ridemsg = "";

        if(ridee && !valid_move(ridee)) 
           return notify_fail("��������߶����ˡ�\n");
           
if(me->is_ghost()&&domain_file(base_name(environment(me)))!="death")
 {              
 	        write(BLU"ͻȻ�������������������һ��ն�������ɭ������:������Ӵ������Ӵ!��\n"NOR);
		write(HIW"һ���������������������ֻص��˹��Ź�\n"NOR);
                me->move("/d/death/gate");
                return 1;
 }
	if( me->is_fighting() ) {
		mout = ridemsg + "��" + dir + "��Ķ����ˡ�\n";
		min = ridemsg + "����ײײ�����˹�����ģ����Щ�Ǳ���\n";
	} else {
		if (me->query("position"))
		     ridemsg += "̤��һ������";
	        else
		     ridemsg += "����һ������";
		//Jiz. 02/11

                if (objectp(thing = my_armor["cloth"]))
                        ridemsg = "����" + thing->query("name");
                else
		if (userp(me))
                        ridemsg = "ȫ���������";
		else
			ridemsg = "";

                if (objectp(thing = my_temp["weapon"]))
                        ridemsg += "��ִ"+ thing->query("name");

		if( ridee && ridee->query("bird") ) {
			mout = ridemsg+ "��" + dir + "��ȥ��\n";
			min = ridemsg+ "���˹�����\n";
		} else {
 		 	mout = ridemsg+ "��" + dir + "�뿪��\n";
			min = ridemsg+ "���˹�����\n";
		}
	}

	if( !wizardp(me) || !me->query("env/invisibility") )
	{
	    	if (environment(me) && environment(me)->query("no_look"))
		    	message( "vision", "һ��ģ����Ӱ��" +  mout, environment(me), ({me}) );
		else
			message( "vision", me->name() + mout, environment(me), ({me}) );
	}
	if( (! ridee || ridee->move(obj)) && me->move(obj, silent) ) {
		me->remove_all_enemy();
		if( !wizardp(me) || !me->query("env/invisibility") ) {
	    			if (environment(me) && environment(me)->query("no_look"))
		    			message( "vision", "һ��ģ����Ӱ��" +  min, environment(me), ({me}) );
				else
					message( "vision", me->name() + min, environment(me), ({me}) );
		}
		me->set_temp("pending", 0);
		// added by snowcat, to fix the bug of recursive move of mutual follow + move to same room 
		if (env != obj)
			all_inventory(env)->follow_me(me, arg);
		if (ridee)
			tell_object (me,"��"+min);
		if (userp(me) && me->query_condition("no_pk_time") &&
		me->query_temp("rumor_time")+10<time() &&
		  MISC_D->find_place(environment(me))!=
		me->query_temp("last_place"))
		{ 
		  me->set_temp("last_place",MISC_D->find_place(environment(me)));
		  msg="��˵ɱ��ͨ����"+HIW+me->query("name")+HIM+"�����"+HIC+me->query_temp("last_place")+HIM+"������û��\n";
		CHANNEL_D->do_channel(this_object(),"rumor",msg);
		me->set_temp("rumor_time",time());
		}
		return 1;
	}

	return 0;
}

void do_flee(object me)
{
	mapping exits;
	string *directions;

	if( !environment(me) || !living(me) ) return;
	exits = environment(me)->query("exits");
	if( !mapp(exits) || !sizeof(exits) ) return;
	directions = keys(exits);
	if (environment(me) && environment(me)->query("no_flee")) return;
	tell_object(me, "�������һ��������ˣ�����\n");
        if( me->query_temp("no_move") ) {
          tell_object (me, "���㱻��ס�ˣ��Ӳ�����\n");
          return;
        }

	if( random(me->query_skill("dodge")/10 + me->query("kar")) < 10 ) {
	   tell_object(me, "������ʧ�ܡ�\n");
	   return;
	}

	main(me, directions[random(sizeof(directions))], 0);
}

int help(object me)
{
	write(@HELP
ָ���ʽ : go <����>
 
������ָ���ķ����ƶ���
 
HELP
    );
    return 1;
}