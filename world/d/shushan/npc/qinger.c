// qinger.c...yushu, 2000.10.24.

inherit NPC;
void create()
{
	set_name("青儿", ({"qing er", "er", "qinger"}));
	//set("title", "");
	set("gender", "女性" );
	set("age", 22);
	set("per", 30);
	set("long", "蜀山派的第三代弟子。\n");
	set("class", "xiake");
	set("combat_exp", 120000);
       set("daoxing", 200000);
       set("attitude", "peaceful");
	create_family("蜀山派", 3, "弟子");
	set_skill("dodge", 80);
	set_skill("zuixian-steps", 80);
	set_skill("parry", 80);
	set_skill("whip", 90);
	set_skill("snowwhip", 80);
	set_skill("force", 80);   
	set_skill("shushan-force", 80);
	set_skill("literate", 100);
	set_skill("spells", 80);
	set_skill("xianfeng-spells", 80);
	map_skill("spells", "xianfeng-spells");
	map_skill("force", "shushan-force");
	map_skill("whip", "snowwhip");
	map_skill("dodge", "zuixian-steps");
       set("max_kee", 500);
	set("max_sen", 500);
	set("force", 1000);
	set("max_force", 800);
	set("mana", 1600);
	set("max_mana", 800);	
	set("force_factor", 40);
	set("mana_factor", 40);

	setup();
	carry_object("/d/obj/cloth/choupao")->wear();
	carry_object("d/obj/weapon/whip/whip")->wield();
}

void attempt_apprentice(object ob)
{
	if( (string)ob->query("family/family_name")=="蜀山派" )
	{
		if( (int)ob->query("family/generation") < 3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师叔见笑了。\n");
			else command("say 师姑见笑了。\n");
		}
		else if( (int)ob->query("family/generation") ==3  )
		{
			if ( (string)ob->query("gender") == "男性" ) command("say 师兄太客气了。\n");
			else command("say 师妹太客气了。\n");
		}
		else 
		{
			command("xixi");
			command("say 你好有趣哦!\n");
			command("recruit " + ob->query("id") );
		}
	}

	else
	{
		command("say 好，我蜀山派一门人才辈出，你可得给师父争气。\n");
		command("recruit " + ob->query("id") );
	}

	return;
}

int recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
		ob->set("class", "xiake");
}

void init()
{
::init();
        add_action("do_yao", "yao");
}

int do_yao(string arg)
{
        object m,mm;
        message_vision("$N向青儿问道：青儿，开饭了吗？\n", this_player());

        if((int)this_player()->query("food") >=
             (int)this_player()->max_food_capacity()*90/100 )
        return notify_fail("青儿笑道：饿啦，还没做好呢！\n");

        if((present("gongbao jiding", this_player())))
        return notify_fail("青儿笑道：不要拿着手里的，还看着锅里的! 馋鬼!\n");
	
	 if ( present("gongbao jiding", environment()) )
         return notify_fail("青儿笑道：那不是有一盘嘛，吃完再说！\n");

        m=new("d/obj/food/dishes/dish10");
        mm=new("d/obj/food/dishes/dish10");


        m->move(this_player());
        mm->move(this_player());
             
        command("snicker");
        message_vision("青儿对$N笑道：饿了吧，慢点吃，小馋鬼!\n", this_player());
        return 1;
}





�