//sgzl

inherit ROOM;
#include <ansi.h>
void create ()
{
set ("short", BLK"黑暗之渊"NOR);
  set ("long", @LONG
[1;31m这里就是通往阿修罗界之路,一条通向死亡,[2;37;0m
[1;31m通向痛苦,通向罪恶的黑暗之路.[2;37;0m
[1;31m四周魔气森森,让人不寒而栗![2;37;0m
LONG);

  set("exits", ([
      ]));

  set("objects", ([
         __DIR__"npc/gui" : 2,
      ]));

  setup();
}

void init ()
{
  add_action ("do_go", "go");
}

int do_go (string dir)
{
    object who = this_player();
    string *names = ({
    "west",
    "east",
    "south",
    "north",
    });


    if (! dir)
      return 0;

    if (who->query("kee")>50)  who->add("kee",-80); 
    else
      {
      who->unconcious();
      return 1;
      }


    if (random(5))
      {
      message_vision ("$N努力地寻找着出口。\n",who);
      }
    else
    {
      if (dir != names[random(sizeof(names))])
        {
        message_vision ("$N终于找到一丝缝隙，冲了出去。\n",who);
        who->move(__DIR__"lu4");
        return 1;
        }
      else
        {
        message_vision ("$N终于找到一丝缝隙，冲了出去。\n",who);
        who->move(__DIR__"lu2");
        return 1;
        }
    }



  return 0;
}


