// by happ@YSZZ
inherit ROOM;
#include <hen.h>

void create ()
{
  set ("short", "奮瞳糾");
  set ("long", @LONG

[1;37m�亜�！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！��
[1;31m  ！[37;41m 園催 [31;40m！[37;41m 斌      瞳 [31;40m！！[37;41m 丼            嬬 [31;40m！！[37;41m 勺     鯉 [31;40m！
[37m     [1;35m[[37m 1[35m]     [36m挫郭議奮麗      [37m悶薦志鹸50            [33m50           
[37m     [1;35m[[37m 2[35m]     [36m胆龍議巣奮      [37m悶薦志鹸100           [33m120          
[37m     [1;35m[[37m 3[35m]     [36m挫喘寄温来      [37m悶薦志鹸500           [33m500          
[37m     [1;35m[[37m 4[35m]     [36m寇酷議痩屮      [37m悶薦志鹸1000          [33m1000          
[37m     [1;35m[[37m 5[35m]     [36m認定繁歌藍      [37m隈薦志鹸500           [33m800          
[37m     [1;35m[[37m 6[35m]     [36m爺表僣遷        [37m隈薦悶薦恷寄          [33m10000         
[1;37m�検�！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！��
LONG);

  set("exits", ([ /* sizeof() == 4 */
         "west": __DIR__"road3",
]));

        setup();
}

void init()
{
        add_action("do_buy","buy");
}

int do_buy(string arg)
{
        object ob = this_player();

        switch(arg)
        {
                case "1":
                {
                if( ob->query("hen/money") < 50 )
                        {
                        write("低峪嗤"+ob->query("hen/money")+"圷阻。\n");
                        return 1;
                        }
                cat(BUYFOOD);
                ob->add("hen/inventory/food",1);
                ob->add("hen/money",-50);
                write("低択阻匯芸奮麗。\n");
                break;
                }
                
                case "2":
                {
                if( ob->query("hen/money") < 120 )
                        {
                        write("低峪嗤"+ob->query("hen/money")+"圷阻。\n");
                        return 1;
                        }
                if( random(2) == 0 )
                cat(BUYLS1);
                cat(BUYLS2);
                ob->add("hen/inventory/lingshi",1);
                ob->add("hen/money",-120);
                write("低択和阻匯芸巣奮。\n");
                break;
                }

                case "3":
                {
                if( ob->query("hen/money") < 500 )
                        {
                        write("低峪嗤"+ob->query("hen/money")+"圷阻。\n");
                        return 1;
                        }
                cat(BUYDABU);
                ob->add("hen/inventory/dabu",1);
                ob->add("hen/money",-500);
                write("低択阻匯薪寄温来。\n");
                break;
                }

                case "4":
                {
                if( ob->query("hen/money") < 1000 )
                        {
                        write("低峪嗤"+ob->query("hen/money")+"圷阻。\n");
                        return 1;
                        }
                write("低択阻匯薪痩屮。\n");
                ob->add("hen/inventory/lingzhi",1);
                ob->add("hen/money",-1000);
                break;
                }
               
                case "5":
                {
                if( ob->query("hen/money") < 800 )
                        {
                        write("低峪嗤"+ob->query("hen/money")+"圷阻。\n");
                        return 1;
                        }                write("低択阻匯薪繁歌。\n");
                ob->add("hen/inventory/renshen",1);
                ob->add("hen/money",-800);
                break;
                }
                case "6":
                {
                if( ob->query("hen/money") < 10000 )
                        {
                        write("低峪嗤"+ob->query("hen/money")+"圷阻。\n");
                        return 1;
                        }
                write("低択阻匯薪僣遷。\n");
                ob->add("hen/inventory/xuelian",1);
                ob->add("hen/money",-1000);
                break;
                }
        }
return 1;
}

