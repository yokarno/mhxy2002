//By tianlin@mhxy for 2001.9.18
//在制作此商店时,我想要是和他们一样都设在npc身上去买东西,有点不大好,
//(1)是npc容易被杀害,要是你给npc设上no_die也行,不过也不怎么地,还没有新
//鲜感,(2)是设在ROOM里面的话,以上的问题就解决了,而且ROOM还很华丽,我自任
//为不错,大家可以模仿的作一下,请不要改作者的名字..谢谢!!!(xixi)
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short", HIB"道具店"NOR);
  set ("long", @LONG

[1;33m┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
[1;31m  —[37;41m 编号 [31;40m—[37;41m 商      品 [31;40m——[37;41m 效            能 [31;40m——[37;41m 价     格 [31;40m—
[37m     [1;35m[[32m 1[35m]     [32m辟谷丸          [37m将食物和饮水加到瓶颈[2;37;0m       [36m2[33m两[1;33m黄金           
[37m     [1;35m[[32m 2[35m]     [36m泻药            [37m将食物和饮水降为0[2;37;0m          [36m5[33m两[1;33m黄金          
[37m     [1;35m[[32m 3[35m]     [33m仙药            [37m只要吃一包就能恢复气血上限[2;37;0m [36m10[33m两[1;33m黄金          
[37m     [1;35m[[32m 4[35m]     [31m神药            [37m只要吃一包就能恢复精神上限[2;37;0m [36m10[33m两[1;33m黄金          
[37m     [1;35m[[32m 5[35m][2;37;0m     [33m千年人参王      [1;37m恢复气血和精神500点[2;37;0m        [36m50[33m两[1;33m黄金          
[37m     [1;35m[[32m 6[35m]     [37m百宝袋          [37m可以无限的装东西[2;37;0m           [36m70[33m两[1;33m黄金         
[37m     [1;35m[[32m 7[35m]     [33m纪念币          [37m加10点悟性[2;37;0m                 [36m20[33m两[1;33m黄金         
[37m     [1;35m[[32m 8[35m][2;37;0m     [31m杀气丸          [1;37m加杀气100点[2;37;0m                [36m9[33m两[1;33m黄金         
[37m     [1;35m[[32m 9[35m]     [35m百年猕猴桃王    [37m加10点内力和10点法力最大值[2;37;0m [36m15[33m两[1;33m黄金         
[37m     [1;35m[[32m10[35m]     [36m天山雪莲        [37m恢复内力和法力最大值[2;37;0m       [36m200[33m两[1;33m黄金         
[37m     [1;35m[[32m11[35m]     [31m万年灵芝        [37m加法力最大值20点[2;37;0m           [36m100[33m两[1;33m黄金         
[1;33m┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛[2;37;0m
LONG);

  set("exits", ([ /* sizeof() == 4 */
        // "enter": __DIR__"road3",
         "out": "/d/city/bingqipu",
         "west": __DIR__"wuqidian",
         "east": __DIR__"kuijiadian",
]));

        setup();
}

void init()
{
        add_action("do_buy","buy");
}

int do_buy(string arg)
{
        object obj;
        object me=this_player();
        int afford;
        if(me->is_busy())
                return notify_fail(CYN"你现在正忙着呢。\n"NOR);
        switch(arg)
        {
                case "1":
                {
                if( !(afford=me->can_afford(20000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(20000);
                obj = new ("/u/tianlin/wuqi/daoju/dan");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一个"HIG"辟谷丸"NOR"。\n");
                break;
                }
                
                case "2":
                {
                if( !(afford=me->can_afford(50000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(50000);
                obj = new ("/u/tianlin/wuqi/daoju/xieyao");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一瓶"HIC"泻药"NOR"。\n");
                break;
                }

                case "3":
                {
                if( !(afford=me->can_afford(100000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(10000);
                obj = new ("/u/tianlin/wuqi/daoju/xianyao");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一包"HIY"仙药"NOR"。\n");
                break;
                }

                case "4":
                {
                if( !(afford=me->can_afford(100000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(10000);
                obj = new ("/u/tianlin/wuqi/daoju/shenyao");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一包"HIR"神药"NOR"。\n");
                break;
                }
 
                case "5":
                {
                if( !(afford=me->can_afford(500000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(500000);
                obj = new ("/u/tianlin/wuqi/daoju/renshen");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"YEL"千年人参王"NOR"。\n");
                break;
                }

                case "6":
                {
                if( !(afford=me->can_afford(700000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(700000);
                obj = new ("/u/tianlin/wuqi/daoju/bag");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一个"HIW"百宝袋"NOR"。\n");
                break;
                }

                case "7":
                {
                if( !(afford=me->can_afford(200000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(200000);
                obj = new ("/u/tianlin/wuqi/daoju/bi");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一块"HIY"纪念币"NOR"。\n");
                break;
                }

                case "8":
                {
                if( !(afford=me->can_afford(90000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(90000);
                obj = new ("/u/tianlin/wuqi/daoju/shaqi");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一粒"RED"杀气丸"NOR"。\n");
                break;
                }

                case "9":
                {
                if( !(afford=me->can_afford(150000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(150000);
                obj = new ("/u/tianlin/wuqi/daoju/taowang");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"HIM"百年猕猴桃王"NOR"。\n");
                break;
                }

                case "10":
                {
                if( !(afford=me->can_afford(2000000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(2000000);
                obj = new ("/u/tianlin/wuqi/daoju/xuelian");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"HIC"天山雪莲"NOR"。\n");
                break;
                }

                case "11":
                {
                if( !(afford=me->can_afford(1000000)) )  {
                write("你带的钱不够。\n");
                return 1;
                } 
                me->pay_money(1000000);
                obj = new ("/u/tianlin/wuqi/daoju/lingzhi");
                obj->move(me);
                me->start_busy(4); 
                write("你向道具店买下一颗"HIR"万年灵芝"NOR"。\n");
                break;
                }
        }
return 1;
}

