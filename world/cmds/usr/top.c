//By tianlin@mhxy for 2002.1.12
//�ҽ���ͻȻ�����ʾ�ĳ�20��player��������ǰ��15����,hehe
//sigh���ǸĻ�ȥ��,hehe

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;
int top_list(object ob1,object ob2);
int get_score(object ob);
int main(object me, string arg)
{
        
        object *list,*ob;
        int i;
        string msg;

      ob = filter_array(objects(), (: userp($1) && !wizardp($1) :));
        list = sort_array(ob, (: top_list :));
      msg =  "\n            �������� "BLINK+HBBLU+HIW+CHINESE_MUD_NAME"���߸������а�"NOR" ��\n";
      msg += "�������������ө������ߩ����������������ө������ߩ������ө��������ө���������\n";
      msg += "��  ���Ρ�  ��      ��        ��      ���� ��    �ɡ� �� ��  �� �� ��  �� ��\n";
      msg += "�ĩ����������ة������������������������ة��������������ة��������ة���������\n";
    for (i = 0 ;i < 10 ; i++) {
if( i >= sizeof(list)) 
    msg += "����ʱ��ȱ������������        ����    ����������      ��    ��  �� ��     ��\n";
        else {
            if( !list[i] ) continue;
            if( !list[i]->query("id") ) continue;
            if(list[i] == me) msg += BMAG HIW;
                  msg += sprintf("��   "HIG"%-5s"NOR"  ��"HIW"%-12s"NOR"  "HIY"%-10s"NOR"��"BMAG""HIC"%-14s"NOR"��"HIB"%8d"NOR"��"HIR"%8d"NOR"��\n"NOR,chinese_number(i+1),list[i]->query("name"),"["+
        capitalize(list[i]->query("id"))+"]", list[i]->query("family")?  list[i]->query("family/family_name"):"��ͨ����",
        get_score(list[i]),get_score(list[i])/100);
                }
                         }
        msg += "����������������������������������������������������������������������������\n";
      //  msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
//�޸ĳ��ճ�ʱ��,��ǰ�����Լ�������������,�����޸�.hehe
	 msg += "  " + BJTIME_D->chinese_time(1,ctime(time())) + "�ǡ�\n";
        msg += "  ����ۺ�������"HBBLU+HIG+get_score(me)+NOR"! \n"NOR;
        write(msg);
        return 1;

}

int top_list(object ob1, object ob2)
{
      int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

      return score2 - score1;
}

int get_score(object ob)
{
        int tlvl,i,score;
        string *ski;
        mapping skills;

        reset_eval_cost();
        skills = ob->query_skills();
        if (!sizeof(skills)) return 1; 
        ski  = keys(skills);
        for(i = 0; i<sizeof(ski); i++) {
                        tlvl += skills[ski[i]];
                        }  // count total skill levels
        score = tlvl/(i+1);
        score += ob->query("max_force")/10;
        score += ob->query("max_mana")/10;
        score += ob->query("str") + ob->query("int") + ob->query("spi") + ob->query("con");
        score += (int)ob->query("combat_exp")/5000;
        score += (int)ob->query("daoxing")/5000;

        return score;
}

int help(object me)
{
write(@HELP
ָ���ʽ : top 
 
���ָ���������֪������ʮ���������Щ����ȥ�����ǡ� 
 
HELP
    );
    return 1;
}