// by happ@YSZZ
inherit ROOM;
#include <hen.h>

void create ()
{
  set ("short", "媚登峰");
  set ("long", @LONG

        如果你想塑造完美曲线，来媚登峰没错！
        （输入[1;31madd[m，体重增加 3 个单位，[1;31msub[m减轻３个单位）

[m
LONG);
  set("exits", ([ /* sizeof() == 4 */
        "east": __DIR__"road7",
]));

        setup();
}

void init()
{
        add_action("do_add","add");
        add_action("do_sub","sub");
}

int do_add()
{
        object ob = this_player();

        if( ob->query("hen/money") < 1000 )
                return notify_fail("你的钱不够来媚登峰拉。\n");
       
        ob->add("hen/weight",3);
        ob->command_function("cls");
        cat(MDF);
        cat(FATTER);
        return 1;
}
int do_sub()
{
        object ob = this_player();

        if( ob->query("hen/money") < 1000 )
                 return notify_fail("你的钱不够来媚登峰拉。\n");

       ob->add("hen/weight",-3);
        ob->command_function("cls");
        cat(MDF);
        cat(THINNER);
        return 1;
}

        
