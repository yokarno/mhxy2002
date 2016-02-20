// by happ@YSZZ
inherit ROOM;
#include <hen.h>

void create ()
{
  set ("short", "教堂");
  set ("long", @LONG

        这里你可以输入 [1;32m  dagong [m 就可以在教堂献爱心喽~~。

LONG);

  set("exits", ([ /* sizeof() == 4 */
        "north": __DIR__"syroad3",
]));

        setup();
}

void init()
{
                add_action("do_work","dagong");
}

int do_work()
{
        object ob = this_player();

        if( !present("zhandou ji",ob) ) return 0;


        ob->command_function("cls");
        ob->command_function("shape");

        ob->add("hen/life",-5);
        ob->add("hen/dirty",7);

        cat(CHAPEL);

        if( time() - ob->query("hen/last_jiaotang") < 180 )
        {
        write("看来小鸡很讨厌重复做同一件事情。\n");
        ob->add("hen/affection",-1);
        return 1;
        }

        ob->add("hen/money",100+random(20));
        ob->set("hen/last_jiaotang",time());
        ob->add("hen/love",1);
        ob->add("hen/ethics",1);
        return 1;
}
