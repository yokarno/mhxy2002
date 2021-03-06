// laozhang.c

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("老张", ({ "lao zhang", "zhang", "lao" }));
	set("long", 
		"他是天鹏府的管家。\n");
          set("title", YEL"天鹏府管家"NOR);
	set("gender", "男性");
       set("class", "xian");
	set("age", 55);
	set("attitude", "peaceful");
	set("per", 16);

	set("str", 20);

	set("combat_exp", 115763);
	set("daoxing", 500000);
	set("max_force", 1500);
       set("force", 1500);
       set("max_mana", 1500);
       set("mana", 1500);

	set_skill("force", 60);
	set_skill("dodge", 60);
	set_skill("spells", 60);
	set_skill("tianpeng-force", 60);
	set_skill("xbuddhism", 60);
	set_skill("sougu-zhua", 60);
	set_skill("rake", 60);
	set_skill("yanxing-steps", 60);
	set_skill("skyriver-rake", 60);
	set_skill("unarmed", 60);	
	set_skill("parry", 60);
	set_skill("literate", 30);
	map_skill("rake", "skyriver-rake");
	map_skill("parry", "sougu-zhua");
	map_skill("unarmed", "sougu-zhua");
	map_skill("force", "tianpeng-force");
	map_skill("spells", "xbuddhism");
	map_skill("dodge", "yanxing-steps");

	create_family("天鹏府", 3, "弟子");

	setup();
	
           carry_object("/d/tianpeng/obj/gangpa")->wield();
           carry_object("/d/tianpeng/obj/choupao")->wear();
}
void attempt_apprentice(object ob)
{
        command("pat "+ob->query("id"));
        command("say 好，希望" + RANK_D->query_respect(ob) +
"多加努力，把我们天鹏府发扬光大。\n");
        message("shout", HIW"〖"HIC"门派消息"HIW"〗："HIY"天鹏府"NOR+WHT"又多了一个弟子"+YEL+this_player()->name()+NOR+WHT"天鹏府的势力加强了。\n"NOR,users());
 command("recruit " + ob->query("id") );
        return;
}

int recruit_apprentice(object ob)
{
        if( ::recruit_apprentice(ob) )                                                                                                                                                                                                     
               ob->set("class","xian");
                ob->set("per",11);
}
�
