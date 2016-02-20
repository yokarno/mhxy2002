#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#define NULL_VALUE 0
inherit CLOTH;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;
inherit F_CLEAN_UP;
string query_autoload() { return 1 + "OK"; }

string inputstr,verb;

void create()
{
       seteuid(getuid());
       set("long",@LONG
                  ��ڤѪ��
����������������������������������������������������
�������� ��    ��  ��       ��Note & description  ��
����������������������������������������������������
��fill  ��fill <id>        �������ָ�ĳ�˵ľ���   ��   
����������������������������������������������������
��whereis ��whereis or<id>  ���г����������˵�λ�á�
��pk      ��pk<ob> with <id>����ĳ��ɱĳ��        ��
��chuqiao ��chuqiao <id>    ���Ž�ɱĳ��          ��
��xing    ��xing <id>       ����ĳ������          ��
��yun     ��yun  <id>       ����ĳ���ε�          ��
��qshs    ��qshs <id>       ����������(�ָ�ԭ�书)��
LONG
       );
       set("unit","��");

       set("no_get",1);

       set("material", "cloth");
       set("armor_prop/armor", 999999999);
       set("light",1);
       setup();
}

void init()
{
       seteuid(geteuid());
       set_name(RED "��ڤѪ��" NOR, ({ "yi", "ander" }));
        add_action("full","fill"); 
       add_action("hun","nofill");
         add_action ("whereis", "whereis"); 
       add_action ("pk_mob", "pk");       
       add_action ("do_wakeup", "xing");  
       add_action ("do_hun","yun");       
       add_action ("do_die","chuqiao");
        add_action ("do_reincarnate","qshs");
  
       this_player()->set_temp("heat",1);
}
int whereis(string arg)
{
  object where, me, fd;
  object *ob;
  string msg;
  int i;
  if (arg!=NULL_VALUE){
    fd = LOGIN_D->find_body(arg);
    if (!fd) return notify_fail("��ڤѪ��˵�����������Ϻ���û�����ѽ����\n");
    }
  me = this_player();
  if (arg) {
    where = environment(find_player(arg));
    if (!where) return notify_fail ("��������Ʈ��䡣\n");
    msg = where->query ("short")+"  -- "+file_name(where)+"\n";
    msg += where->query("long");
  }
 else {

    ob = users();
    msg = "";
    for(i=0; i<sizeof(ob); i++) {
      where = environment(ob[i]);
      if (!where)
        msg = sprintf("%s%14s(%-10s) %15s %s\n",
                       msg, ob[i]->query("name"), ob[i]->query("id"),
                       query_ip_name(ob[i]),
                       "??????????");
      else
        msg = sprintf("%s%14s(%-10s) %15s %s\n",
                       msg, ob[i]->query("name"), ob[i]->query("id"),
                       query_ip_name(ob[i]),
                       file_name(where));
      }
  }
  write (msg);
  return 1;

}

int full(string str) 
{  int max;
  object me;

       if (!geteuid()) seteuid (getuid());
       if(!str)
       me=this_player();
       else   {
       me = LOGIN_D->find_body(str);
       if (!me) return notify_fail ("��ڤѪ��˵�����������: �Ҳ���"+str+"\n");
       }
  max = me->query("max_jing");
  me->set("eff_jing",max);
  me->set("gin",max);
  max = me->query("max_qi");
  me->set("eff_qi",max);
  me->set("qi",max);
  max = me->query("max_sen");
  me->set("eff_sen",max);
  me->set("sen",max);
  max = me->max_food_capacity();
  me->set("food",max);
  max = me->max_water_capacity();  


  me->set("water",max);
  max = me->query("max_jing");
  me->set("eff_jing",max);


  me->set("jing",max);
  max = me->query("max_qi");
  me->set("eff_qi",max);
  me->set("qi",max);
  max = me->query("max_shen");
  me->set("eff_shen",max);
  me->set("shen",max);

  max = me->max_food_capacity();
  me->set("food",max);
  max = me->max_water_capacity();  
  me->set("water",max);
  me->clear_condition();
  message_vision( sprintf("$N������մ󺰣���Զ������\n"),
                  this_player());

  return 1; 
}
int pk_mob(string str)
{
        object ob1,ob2;
        string st1,st2;
        if (!str || str=="") return notify_fail ("��ڤѪ��˵��������˭ PK ˭��\n");
        if (sscanf( str,"%s with %s",st1,st2)!=2 )
           return notify_fail ("mobpk <ob1> with <ob2>\n");

        if (!ob1=present(st1,environment(this_player

())))
          return notify_fail("�Ҳ��� "+st1+" �������.\n");

        if (!ob2=present(st2,environment(this_player())))

          return notify_fail("�Ҳ��� "+st2+" �������.\n");



       message_vision(HIR ""+ob1->name()+"����"+ob2->name()+"���һ����������������\n" NOR,
       this_player());
               ob1->kill_ob(ob2);
               return 1;
}

int do_give (string str)
{
  object me, ob, who;
  string wiz, obs, whos;
  if (str!=NULL_VALUE) return notify_fail("usage:gei <id>\n");
  me = this_player();
  if (sscanf (str, "%s to %s", obs, whos)!= 2)
     return 0;
  wiz = wizhood (me);
  if (obs != "cloak" && obs != "wiz cloak") return 0;
  write ("my level : "+wiz_level(me)+"\n");
  if (wiz_level(me) > 1)
  if ((wiz = SECURITY_D->get_boss(whos)) == "" || (wiz != me->query("id"))) {
   write ("��ڤѪ��˵�����ҿ����Ǳ�����ɣ���\n");
  return 1;
  }


  ob = present ("wiz cloak", me);
  if (!ob) write ("��û������������\n");
  who = find_player(whos);
  if (!who) write ("û������ˡ�\n");
  if (ob && who) {
    ob->move (who);
    message_vision (RED "$N��$nһ����������������ڤѪ�¡���\n" NOR, me, who);
  }
  return 1;
}

int do_wakeup (string str)
{
  object who;

  if (!str) return notify_fail ("usage:xing <id>\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
 return notify_fail ("��ڤѪ��˵������ û��"+str+"��\n");


  }
  who->remove_call_out("revive");
  who->revive();
  who->reincarnate();
  write("Ok.\n");
  return 1;
}

int do_hun (string str)
{
  object who;

  if (!str) return notify_fail ("��ڤѪ��˵���㲻�ܰ����Լ�Ū�Σ�\n");
  who = LOGIN_D->find_body(str);
  if (!who){ 
  if (!(who=present (lower_case(str), environment(this_player()))) )
    return notify_fail ("��ڤѪ��˵������ û��"+str+"��\n");
  }

  who->remove_call_out("unconcious");
  who->unconcious();
  who->announce();
 write("Ok.\n");
  return 1;
}
int do_die (string str)
{
  object ob;
  if (!str) return notify_fail("usage: chuqiao <oneself id>\n");
  ob = LOGIN_D->find_body(str);
  if (!ob) return notify_fail("û�����ʣ�û����ˡ�\n");
  message_vision( sprintf(HIY "ֻ��$N���ֶ������һָ����У����������ʡ���\nһ�Ѿ޽���$N����Ľ�����ɳ���ֱ������...\n" NOR),
         this_player());
  tell_room(environment(ob),"����к�Ȼ������һ�Ѿ޴�ı�����ֱ��վ���Ǳߵ�"+                    
       (string)ob->query("name")+"��ȥ��\n" , ob);
  tell_object(ob,"���Ȼ���������һ����������ľ޴󱦽���������..\n ������һ��...");  
  ob->die();
  message_vision( sprintf( HIY "ֻ��$N���ֶ������һָ����У����������ʡ���\nһ�Ѿ޽�������лص���$N����Ľ����\n" NOR),
         this_player());
  write("Ok.\n");
  return 1;
}
int do_reincarnate (string str)
{
 object ob;
  if (!str) return notify_fail("usage: qshs <id>\n");
       ob = LOGIN_D->find_body(str);
 if (!ob) return notify_fail("���������?\n");
  if (ob->is_ghost()) 
           tell_object(ob,"�������ȫ�������...\n");
       else 
       return notify_fail("��...����˺����ǻ�ģ�\n");
  tell_object(ob,"�����ϣ����ǹ�!��Ҫ���㸴��ұ����ϴε�һ�С�\n");
  tell_room(environment(ob),"һ�����ͻȻ��������£�������"+
       (string)ob->query("name")+"����Χ��\n", ob);
   
    tell_object(ob,"ͻȻһ����������������𣬡������....��������\n��ʼ���ٲ��ǻ���ˡ�����ͻȻ�е�һ�����...\n");
  ob->reincarnate();
  ob->query_temp("last_damage_from");  
  tell_object(ob,"�ܺã����ָ����ˣ�\n");
  write("Ok.\n");
  return 1;    
}

