// 神话世界·西游记·版本４．５０
/* <SecCrypt CPL V3R05> */
 
#include <room.h>
inherit ROOM;

void create ()
{
  set ("short", "[31m大殿殿门[m");
  set ("long", @LONG

这就是灵霄宝殿的殿门了,门上高高挂着一块匾,上面刻着有
「灵霄宝殿」四个大字,周围有一些天兵天将.再往北就是正殿了.
LONG);

  set("exits", ([ /* sizeof() == 1 */
  "north" : __DIR__"dadian",
   "south" :__DIR__"bridge",
]));


  set("objects", ([ /* sizeof() == 1 */
  __DIR__"npc/tian-bing" : 3,
  __DIR__"npc/tian-jiang" : 1,
]));

  setup();
}
int valid_leave(object me, string dir)
{
   if (dir == "north" ) {
        if (objectp(present("tian jiang", environment(me))))
   return notify_fail("天将喝道:未得陛下宣召,不得入殿!!\n");
        if (objectp(present("tian bing", environment(me))))
       return notify_fail("天兵喊道：我家将军不在，小人不敢放您进去！\n");
}
       return ::valid_leave(me, dir);
}
