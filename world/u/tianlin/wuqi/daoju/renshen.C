//By tianlin@mhxy for 2001.9.20�޸�
#include <ansi.h>

inherit ITEM;

int do_eat(string);
void init();

void init()
{
  if (!wizardp(this_player())) {
  }                                    
  add_action("do_eat", "eat");
}

void create()
{
  set_name(YEL"ǧ���˲���"NOR, ({"qiannian renshen","renshenwang","renshen"}));
  set_weight(20);
  if (clonep())
    set_default_object(__FILE__);
  else {
    set("unit", "��");
    set("long", "����һ��ǧ����˲�����ʮ�����\n");
    set("value", 2000000);
    set("drug_type", "��Ʒ");
  }
  
  setup();
}

int do_eat(string arg)
{
  int qixue, jingshen, buman;
  object me = this_player();
  
  if (!id(arg))
    return notify_fail("��Ҫ��ʲô��\n");
    qixue = me->query("eff_kee") - me->query("kee");
    buman = qixue * 50 / (int)me->query_skill("force");
    if(buman < 1)
         return notify_fail(WHT"������û�е�"NOR+HIR"��Ѫ"NOR+WHT"����\n"NOR);

    jingshen = me->query("eff_sen") - me->query("sen");
    buman = jingshen * 50 / (int)me->query_skill("force");
    if(buman < 1)
         return notify_fail(WHT"������û�е�"NOR+HIC"����"NOR+WHT"����\n"NOR);

  me->add("kee",500);
  me->add("sen",500);
  message_vision(HIY "$N����һ��"NOR+YEL"ǧ���˲�"NOR+HIY",�о��Լ��ֳ����������� \n" NOR, me);
  
  destruct(this_object());
  return 1;
}