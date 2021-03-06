// the wizard part modified by vikee for xlqy 
// look.c
// "per" parts modified by none at 96/10/02

#pragma save_binary
#include <room.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int look_room(object me, object env);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string status_color(int current, int max);
string do_query(object obj);
// mon 6/6/98
string *peep_msg = ({
	"好像有人探头探脑地向这边张望了几眼。\n",
	"$N探头探脑地向这边张望了几眼。\n",
	"你忽然觉得似乎有双眼睛在背后盯着你看。\n",
	});

string *look_level_boy = ({
 BLU "眉歪眼斜，瘌头癣脚，不象人样\n" NOR,
 BLU "呲牙咧嘴，黑如锅底，奇丑无比\n" NOR,
 BLU "面如桔皮，头肿如猪，让人不想再看第二眼\n" NOR,
 HIB "贼眉鼠眼，身高三尺，宛若猴状\n" NOR,
 HIB "肥头大耳，腹圆如鼓，手脚短粗，令人发笑\n" NOR,
 NOR "面颊凹陷，瘦骨伶仃，可怜可叹\n" NOR,
 NOR "傻头傻脑，痴痴憨憨，看来倒也老实\n" NOR,
 NOR "相貌平平，不会给人留下什么印象\n" NOR,
 YEL "膀大腰圆，满脸横肉，恶形恶相\n" NOR,
 YEL "腰圆背厚，面阔口方，骨格不凡\n" NOR,
 RED "眉目清秀，端正大方，一表人才\n" NOR,
 RED "双眼光华莹润，透出摄人心魄的光芒\n" NOR,
 HIY "举动如行云游水，独蕴风情，吸引所有异性目光\n" NOR,
 HIY "双目如星，眉梢传情，所见者无不为之心动\n" NOR,
 HIR "粉面朱唇，身姿俊俏，举止风流无限\n" NOR,
 HIR "丰神如玉，目似朗星，令人过目难忘\n" NOR,
 MAG "面如美玉，粉妆玉琢，俊美不凡\n" NOR,
 MAG "飘逸出尘，潇洒绝伦\n" NOR,
 MAG "丰神俊朗，长身玉立，宛如玉树临风\n" NOR,
 HIM "神清气爽，骨格清奇，宛若仙人\n" NOR,
 HIM "一派神人气度，仙风道骨，举止出尘\n" NOR,
});

string *look_level_girl = ({
  BLU "丑如无盐，状如夜叉\n" NOR,
  BLU "歪鼻斜眼，脸色灰败，直如鬼怪一般\n" NOR,
  BLU "八字眉，三角眼，鸡皮黄发，让人一见就想吐\n" NOR,
  HIB "眼小如豆，眉毛稀疏，手如猴爪，不成人样\n" NOR,
  HIB "一嘴大暴牙，让人一看就没好感\n" NOR,
  NOR "满脸疙瘩，皮色粗黑，丑陋不堪\n" NOR,
  NOR "干黄枯瘦，脸色腊黄，毫无女人味\n" NOR,
  YEL "身材瘦小，肌肤无光，两眼无神\n" NOR,
  YEL "虽不标致，倒也白净，有些动人之处\n" NOR,
  RED "肌肤微丰，雅淡温宛，清新可人\n" NOR,
  RED "鲜艳妍媚，肌肤莹透，引人遐思\n" NOR,
  HIR "娇小玲珑，宛如飞燕再世，楚楚动人\n" NOR,
  HIR "腮凝新荔，肌肤胜雪，目若秋水\n" NOR,
  HIW "粉嫩白至，如芍药笼烟，雾里看花\n" NOR,
  HIW "丰胸细腰，妖娆多姿，让人一看就心跳不已\n" NOR,
  MAG "娇若春花，媚如秋月，真的能沉鱼落雁\n" NOR,
  MAG "眉目如画，肌肤胜雪，真可谓闭月羞花\n" NOR,
  MAG "气质美如兰，才华馥比山，令人见之忘俗\n" NOR,
  HIM "灿若明霞，宝润如玉，恍如神妃仙子\n" NOR,
  HIM "美若天仙，不沾一丝烟尘\n" NOR,
  HIM "宛如"+HIW+"玉雕冰塑"+HIM+"，似梦似幻，已不再是凡间人物\n" NOR,
});

string *per_msg_kid1 = ({
        CYN "月眉星眼，灵气十足。\n" NOR,
        CYN "机灵活泼，神态非凡。\n" NOR,
        CYN "面若秋月，色如晓花。\n" NOR,
});

string *per_msg_kid2 = ({
        CYN "隆额大眼，脸色红润。\n" NOR,
        CYN "胖胖嘟嘟，逗人喜欢。\n" NOR,
        CYN "细皮嫩肉，口齿伶俐。\n" NOR,
});

string *per_msg_kid3 = ({
        CYN "身材矬矮，傻里傻气。\n" NOR,
        CYN "肥肥胖胖，小鼻小眼。\n" NOR,
        CYN "呆头呆脑，笨手笨脚。\n" NOR,
});

string *per_msg_kid4 = ({
        CYN "蓬头垢脚，脸黄肌瘦。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao1 = ({
        HIB "脸上隐隐泛出一股煞气。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao2 = ({
        HIB "身上围绕着一阵黑雾。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao3 = ({
        HIB "身上围绕着一团黑云。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_yao4 = ({
        HIB "整个笼罩在一团妖气之中。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian1 = ({
        HIY "脸上显出一股祥和之气。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian2 = ({
        HIY "身上围绕着一团瑞气。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian3 = ({
        HIY "身边围绕着一朵祥云。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});

string *pos_msg_xian4 = ({
        HIY "整个笼罩在"HIW"七"HIR"彩"HIM"祥"HIC"云"HIY"之中。\n" NOR,
        CYN "神如木鸡，面有病色。\n" NOR,
        CYN "五官不整，四肢不洁。\n" NOR,
});
string chinese_time(int type,string get_time)
{
        string e_time, week, month, year;
        string c_week, c_year, c_month, c_time;
        int day, hour, minute, second;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul",
		"Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        if ( stringp(get_time) )
                e_time = get_time;
        else e_time = ctime(time());

        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        c_week  = chinese_number(member_array(week, week_name) + 1);

        c_month = chinese_number(member_array(month, month_name) + 1);

        c_year  = sprintf("%s%s%s%s",
                         chinese_number(year[0]-48),
                         chinese_number(year[1]-48),
                         chinese_number(year[2]-48),
                         chinese_number(year[3]-48));

        c_year = c_year + "年";
        c_month  = c_month + "月";
        c_week = " 星期"+c_week;

        c_time = chinese_number(day) + "日";
        c_time += chinese_number(hour) + "点";
        c_time += chinese_number(minute) + "分";
        // maybe not need srcond to show
        c_time += chinese_number(second) + "秒";

        if (type) {
                switch( type ) {
                        case 5: return c_year+c_month+c_time+c_week;
                        case 2: return c_year+c_month+c_time;
                        case 3: return c_month+c_time+c_week;
                        case 4: return c_month+c_time;
                        case 1: return year+"年"+(member_array(month, month_name) + 1)+
				"月"+day+"日"+hour+"点"+minute+"分"+second+"秒";
                        case 6: return (member_array(month, month_name) + 1)+
				"月"+day+"日"+hour+"点"+minute+"分";
                        case 7: return year+"/"+(member_array(month, month_name) + 1)+
				"/"+day+"";
                        default: return c_year+c_month+c_time+c_week;
                        }
                }
        return c_year+c_month+c_time+c_week;
}
// snowcat 12/20/97
string ride_suffix (object me)
{
  string ridemsg = 0;
  object ridee = 0;

  ridee = me->ride();
  if (ridee)
    ridemsg = ridee->query("ride/msg")+"在"+ridee->name()+"上";
  return ridemsg;
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object obj;
	int result;

	if( !arg ) result = look_room(me, environment(me));
	else if( (obj = present(arg, me)) || (obj = present(arg, environment(me)))) {
		if( obj->is_character() ) result = look_living(me, obj);
		else result = look_item(me, obj);
	} else result = look_room_item(me, arg);

	return result;
}

int look_room(object me, object env)
{
	int i;
	object *inv;
	mapping exits;
	string str, str1="", str2="", str3="", *dirs;
	string ridemsg = "";

	if( !env ) {
		write("你的四周灰蒙蒙地一片，什么也没有。\n");
		return 1;
	}
    str = sprintf( "%s  %s\n    %s%s",
     env->query("short")?(env->query("outdoors")?""HIR"「[2;37;0m"WHT+(string)env->query("short")+NOR+HIC"[31m」[2;37;0m"NOR:HIR"「[1;30m[4;53m"+(string)env->query("short")+NOR HIR"」"NOR): "",
     wizardp(me)?NOR HIR+" ──   "NOR MAG+file_name(env)+NOR: "",
     env->query("long")? env->query("long"): "\n",
     env->query("outdoors")? NATURE_D->outdoor_room_description() : "" );

	if( mapp(exits = env->query("exits")) ) {
		dirs = keys(exits);
		for(i=0; i<sizeof(dirs); i++)
			if( (int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
				dirs[i] = 0;
		dirs -= ({ 0 });
		if (env->query("no_look") && !wizardp(me))
			str += CYN"    这里的出路看不清楚。\n"NOR;
		else if( sizeof(dirs)==0 )
			str += HIB"    这里没有任何明显的出路。\n"NOR;
		else if( sizeof(dirs)==1 ) {
			str += "    这里唯一的出口是" + YEL + dirs[0] + NOR;
		//	str += "    这里唯一的出口是" + BOLD + dirs[0] + NOR;
			if (env->query("no_look"))
			    	str += "<看不见>";
			str += "。\n";

		} else {
			str += sprintf("    这里明显的出口是 " + BOLD + "%s" + NOR + " 和 " + BOLD + "%s" + NOR,
	//		str += sprintf("    这里明显的出口是 " + YEL + "%s" + NOR + " 和 " + YEL + "%s" + NOR,
				implode(dirs[0..sizeof(dirs)-2], "、"), dirs[sizeof(dirs)-1]);
			if (env->query("no_look"))
			    	str += " <看不见>";
			str += "。\n";
		} 
	
}
//	str += env->door_description();
	inv = all_inventory(env);
	i=sizeof(inv);
	str2 = "";
	while(i--) {
	    	str1 = "";
		if( !me->visible(inv[i]) ) continue;
		if( inv[i]==me ) continue;
		if (env->query("no_look"))
		{
		    	str1 += "  " + "模糊的影子";
			if (! wizardp(me))
			{
			    	str1 += "\n";
				str += str1;
			    	continue;
			}
		}
		if (ridemsg = ride_suffix(inv[i]))
			str1 += "  " + inv[i]->short() + " <"+ridemsg +
			  ">";
		else	
			str1 += "  " + inv[i]->short();
		if (env->query("no_look"))
		    	str1 += " <看不见>";
	    	str1 += "\n";
		str2 = str1 + str2;
	}
//By tianlin@mhxy for 2002.1.10.从新改编格式
 //By waiwai@mszj 2000/11/03
   if(me->query("look")=="y"){
	  // str3 =HIW+"- "+chinese_time(6,(string)localtime(time()))+" "+NOR;
	if(( me->query("water") > 0 ) || ( me->query("food") > 0 )){
          str3 +=HIY"\n<"NOR CYN"气血:"HIC+me->query("kee")+"/"+me->query("max_kee")+HIY"> ";
          str3 +=HIY"<"NOR CYN"精神:"HIC+me->query("sen")+"/"+me->query("max_sen")+HIY"> ";
          str3 +=HIY"<"NOR CYN"内力:"HIC+me->query("force")+"/"+me->query("max_force")+HIY"> ";
          str3 +=HIY"<"NOR CYN"法力:"HIC+me->query("mana")+"/"+me->query("max_mana")+HIY"> \n"NOR;
          }
      else
	if(( me->query("water") <= 0 ) || ( me->query("food") <= 0 )){
          str3 +=HIY"\n<"NOR CYN"气血:"HIC+me->query("kee")+"/"+me->query("max_kee")+HIY"> ";
          str3 +=HIY"<"NOR CYN"精神:"HIC+me->query("sen")+"/"+me->query("max_sen")+HIY"> ";
          str3 +=HIY"<"NOR CYN"内力:"HIC+me->query("force")+"/"+me->query("max_force")+HIY"> ";
          str3 +=HIY"<"NOR CYN"法力:"HIC+me->query("mana")+"/"+me->query("max_mana")+HIY"> ";
          str3 +=HIY"<"NOR HIB"口渴"+HIY"> ";
          str3 +=HIY"<"NOR WHT"饥饿"+HIY"> \n"NOR;
}}
	write(str+str2+str3);

	return 1;
}

int look_item(object me, object obj)
{
	mixed *inv;

//	write(obj->long());
	me->start_more(obj->long());
	
	//added by weiqi for self-made fabao
	if( obj->query("series_no") && obj->query("fabao") ) 
	    write(obj->show_status());
	
	inv = all_inventory(obj);
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object() );
		message("vision", sprintf("里面有：\n  %s\n",
			implode(inv, "\n  ") ), me);
	}
	return 1;
}
string pos_status_msg(int position)
{ 
  // beeby 7/14/2000
  if (position>0)
  {
     if (position<100)
	return (pos_msg_xian1[0]);
     else if (position<500)
         return (pos_msg_xian2[0]);
     else if (position<1000)
        return (pos_msg_xian3[0]);
     else
        return (pos_msg_xian4[0]);
  } else
    {
     if (position>-100)
        return (pos_msg_yao1[0]);
     else if (position>-500)
         return (pos_msg_yao2[0]);
     else if (position>-1000)
        return (pos_msg_yao3[0]);
     else
        return (pos_msg_yao4[0]);
    }
}
string per_status_msg(int age, int per, string gender)
{
   // added by snowcat
   if (age < 14) {
     if ( per>=25 )
        return ( per_msg_kid1[random(sizeof(per_msg_kid1))]);
     else if ( per>=20 )
        return ( per_msg_kid2[random(sizeof(per_msg_kid2))]);
     else if ( per>=15 )
        return ( per_msg_kid3[random(sizeof(per_msg_kid3))]);
     else    return ( per_msg_kid4[random(sizeof(per_msg_kid4))]);
     }
		
	if ( gender == "男性" ) {
		if ( per>=10&&per<=30 )
			return ( look_level_boy[per-10]);
		else if (per>30)
		       return ( look_level_boy[20]);
		else return "长得怎样你没什么概念。\n";

		}
		
	if ( gender == "女性" ) {
		if ( per>=10&&per<=29 )
			return ( look_level_girl[per-10]);
		else if (per>29)
		       return ( look_level_girl[20]);
		else return "长得怎样你没什么概念。\n";

                }
	else return "";
//	else return "长得怎样你没什么概念。\n";
}

int look_living(object me, object obj)
{
	string str, limb_status, ridemsg, pro;
	mixed *inv;
	mapping my_fam, fam;
// added for bian by mon.
	mapping ofamily;
	string ogender,orace;
	int oage;
       int equip, wearornot;
 
	if(obj->query_temp("d_mana")>0) 
	{
		ofamily=obj->query_temp("family");
		ogender=obj->query_temp("gender");
		orace=obj->query_temp("race");
		oage=obj->query_temp("age");
	} 
	else 
	{
		ofamily=obj->query("family");
		ogender=obj->query("gender");
		orace=obj->query("race");
		oage=obj->query("age");
//fake_age is set as the age when player 不堕轮回。
//so later on, he/she always looks like the age of that time:)
//but need a "look" to activate all the relatived settings...weiqi
//only when one is not in the status of "bian", check his/her
//fake_age. mon 9/4/97
/*
		if(obj->query("life/live_forever") ) 
		{ 
			//set the fake_age if not set...
			if( obj->query("fake_age") ) obj->set("fake_age", oage);

			if( oage>obj->query("fake_age") ) 
			{
			//if "age" is less than fake_age, reset fake_age.
			//mon 9/4/97
				oage=obj->query("fake_age");
			}
			else if( oage<obj->query("fake_age") ) 
			{
				obj->set("fake_age", oage);
			}
		}
	*/



     if(obj->query("life/live_forever") )
       {
          if (!obj->query("fake_age")) obj->set("fake_age",oage);
         if (oage > obj->query("fake_age")) oage=obj->query("fake_age");       }
     if (obj->query_condition("makeup"))
     if (obj->query("fake_age_x"))
         oage=obj->query("fake_age_x");
//done with fake_age
     }
	if( me!=obj && obj->visible(me) && environment(me) &&
	    !environment(me)->query("no_look") )
		message("vision", me->name() + "正盯着你看，不知道打些什么主意。\n", obj);

	str = obj->long();

	str = replace_string(str, "$n", me->name());
	str = replace_string(str, "$N", obj->name());
    str = replace_string(str, "$C", RANK_D->query_respect(obj));
    str = replace_string(str, "$c", RANK_D->query_rude(obj));
	str = replace_string(str, "$R", RANK_D->query_respect(me));
	str = replace_string(str, "$r", RANK_D->query_rude(me));


	pro = (obj==me) ? gender_self(ogender) : gender_pronoun(ogender);

        if(obj->query_temp("d_mana")==0 || obj->query_temp("is_character")) {
	
	if( orace=="人类"
	&&	intp(oage) )
		if(oage<10) {
			str += sprintf("%s看起来显然还不到十岁。\n", pro);
		}
		else{
			str += sprintf("%s是一位%s多岁的%s。\n", pro, chinese_number(oage / 10 * 10),RANK_D->query_respect(obj));
		}

	//check about wife and husband
	if((obj->parse_command_id_list())[0]==me->query("couple/id") ) {
		if( (string)me->query("gender")=="女性" ){
		str += sprintf("%s是你的丈夫。\n", pro);
		}
		else{
			str += sprintf("%s是你的妻子。\n", pro);
		}
	}
	// If we both has family, check if we have any relations.
	if( obj!=me
	&&	mapp(fam = ofamily)
	&&	mapp(my_fam = me->query("family")) 
	&&	fam["family_name"] == my_fam["family_name"] ) {
	
		if( fam["generation"]==my_fam["generation"] ) {
			if( ogender == "男性" )
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师兄": "师弟");
			else
				str += sprintf( pro + "是你的%s%s。\n",
					my_fam["master_id"] == fam["master_id"] ? "": "同门",
					my_fam["enter_time"] > fam["enter_time"] ? "师姐": "师妹");
		} else if( fam["generation"] < my_fam["generation"] ) {
			if( member_array(my_fam["master_id"],
			    obj->parse_command_id_list())>-1  )
				str += pro + "是你的师父。\n";
			else if( my_fam["generation"] - fam["generation"] > 1 )
				str += pro + "是你的同门长辈。\n";
			else if( fam["enter_time"] < my_fam["enter_time"] )
				str += pro + "是你的师伯。\n";
			else
				str += pro + "是你的师叔。\n";
		} else {
			if( fam["generation"] - my_fam["generation"] > 1 )
				str += pro + "是你的同门晚辈。\n";
			else if( fam["master_id"] == me->query("id") )
				str += pro + "是你的弟子。\n";
			else
				str += pro + "是你的师侄。\n";
		}
	}

/*	if( obj->query("max_kee") )
		str += pro + COMBAT_D->eff_status_msg((int)obj->query("eff_kee") * 100 / (int)obj->query("max_kee")) + "\n";
*/

//here, if per>=100, no rong-mao description, it'll be necessary sometimes.
//return special looking first if he/she has one.

	if( obj->query("looking") ){
		str += pro + (string)obj->query("looking") + "\n";
	} else {
	  string looking= per_status_msg((int)obj->query("age"),
	         (int)obj->query_per(), ogender);
              if( strlen(looking)>1 && obj->query("per") < 100 )
        	         str += pro + looking;
	}
	
	ridemsg = ride_suffix(obj);
	if (ridemsg)
		str += pro + "正" + ridemsg + "。\n";
		
        wearornot = 0;
        inv = all_inventory(obj);
        for(equip=0; equip<sizeof(inv); equip++)
        {
                if( inv[equip]->query("equipped") ) wearornot = 1;
        }
        if((wearornot == 0 ) && userp(obj) && !wizardp(obj) )
            str += pro+HIY"全身上下一丝不挂, 难道想裸奔～～～～\n";
        //By waiwai@mszj 2000/11/03
	if( sizeof(inv) ) {
		inv = map_array(inv, "inventory_look", this_object(), obj->is_corpse()? 0 : 1 );
		inv -= ({ 0 });
		if( sizeof(inv) )
			str += sprintf( obj->is_corpse() ? "%s的遗物有：\n%s\n" : "只见%s：\n%s\n",
				pro, implode(inv, "\n") );
	}
        
	}

        me->start_more(str);

	if( obj!=me 
	&&	living(obj)
	&&	random((int)obj->query("bellicosity")/10) > (int)me->query_per() ) {
		write( HIW+obj->name() +HIW "突然转过头来瞪你一眼。\n"NOR);
		COMBAT_D->auto_fight(obj, me, "berserk");
		return 1;
	}

//this part is  taken from attack.c
//mon 1/22/98
/*
	if( obj!=me 
	&& living(obj)
	&& userp(obj)
        && random((int)obj->query("bellicosity")/40) > (int)obj->query("cps") ) 
	  COMBAT_D->auto_fight(obj, me, "berserk");
*/

	return 1;
}

string inventory_look(object obj, int flag)
{
	string str;
	str = obj->short();
	if( obj->query("equipped") )
		str = HIC "  □" NOR + do_query(obj);
	else if( !flag )
		str = "    " + str;
	else return 0;
	return str;
}


int look_room_item(object me, string arg)
{
	object env;
	mapping item, exits;

	if( !objectp(env = environment(me)) )
		return notify_fail("这里只有灰蒙蒙地一片，什么也没有。\n");

	if( mapp(item = env->query("item_desc")) && !undefinedp(item[arg]) ) {
		if( stringp(item[arg]) )
			write(item[arg]);
		else if( functionp(item[arg]) )
			write((string)(*item[arg])(me));
			
		return 1;
	}
    	if (env->query("no_look"))
  		return notify_fail("你什么也看不见。\n");
	if( mapp(exits = env->query("exits")) && exits[arg] && !undefinedp(exits[arg]) ) {
		if( (objectp(exits[arg]) && env=exits[arg]) ||
		    objectp(env = load_object(exits[arg])) ) {
			look_room(me, env);
			if(!me->query("env/invisibility") && random(3)==0
				&& env!=environment(me) ) {
			    string msg=peep_msg[random(sizeof(peep_msg))];
			    msg=replace_string(msg,"$N",me->name());
			    tell_room(env, msg);
			}
		} else {
		  return notify_fail("[34m你什么也看不见。[2;37;0m\n");
		}
		return 1;
	}
	return notify_fail("[36m你要看什么？[2;37;0m\n");
}
string do_query(object obj)
{
        string str,units;

        units =obj->query("unit");
        str = obj->short();
        if (obj->query("armor_type"))
        switch( obj->query("armor_type") ) {
                case "cloth":
                case "armor":
                        str = "身穿一"+ units + str;
                        break;
                case "boots":
                        str = "脚上穿着一" + units + str;
                        break;
                case "head":
                case "neck":
                case "wrists":
                case "finger":
                case "hands":
                        str ="戴着一"+ units + str;
                        break;
                case "waist":
                        str = "腰间绑得有一"+units+str;
                        break;
                case "flower":
                        str = "头上戴着一"+units+str;
                        break;
                default:
                        str = "装备着"+str; 
                        }
        else
        if( obj->wield() )
                if (obj->query("skill_type")=="throwing")
                str ="身上带着"+str;
                else
                str ="手持一" + units + str;
        return str;     
}
string status_color(int current, int max)
{
	int percent;
 
	if( max>0 ) percent = current * 100 / max;
	else percent = 100;
	if( percent > 100 ) return HIC;
	if( percent >= 90 ) return HIG;
	if( percent >= 60 ) return HIY;
	if( percent >= 30 ) return YEL;
	if( percent >= 10 ) return HIR;
	return RED;
}
int help (object me)
{
	write(@HELP
指令格式: look [<物品>|<生物>|<方向>]
 
这个指令让你查看你所在的环境、某件物品、生物、或是方向。
 
HELP
);
	return 1;
}
