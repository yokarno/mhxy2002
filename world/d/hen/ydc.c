// by happ@YSZZ
inherit ROOM;
#include <hen.h>

void create ()
{
  set ("short", "运动场");
  set ("long", @LONG

        生命在于运动，朋友请不要吝啬你的体力，来吧。[1;33m（do_sport）
[m
LONG);
  set("exits", ([ /* sizeof() == 4 */
        "east": __DIR__"road5",
]));

        setup();
}

void init()
{
        add_action("do_sport","do_sport");
}

int do_sport()
{
        object ob = this_player();

        ob->add("hen/weight",-1);
        ob->add("hen/dirty",5);
        ob->command_function("cls");
        ob->command_function("shape");
        cat(SPORT);
        write("运动好处多多啦...\n");
        return 1;
}
