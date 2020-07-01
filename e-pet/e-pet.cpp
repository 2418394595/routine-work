#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>
#include <time.h>
#include <string>
using namespace std;
void instruction();

class pet
{
private:
	int age, hunger, thirsty, mood, health, step;
	int money,prestige;
public:
	pet(int a=0 , int hu = 0, int t = 0, int m = 0, int he = 0, int s = 20, int mon=50,int p=0)
	{
		age = a; hunger = hu; thirsty = t; mood = m; health = he; step = s; money= mon, prestige = p;
	};
	void show()
	{
		cout<< "现在的状态：" << endl<< "年龄" << get_age() << endl << "饥饿值" << get_hunger() << endl << "饥渴值" << get_thirsty() << endl
			<< "心情值" << get_mood() << endl << "健康值" << get_health() <<endl<<"金币数"<<get_money()<<endl<<"声望点"<<get_prestige()<<endl;
	};
	int get_prestige(){ return prestige; };
	int get_money(){ return money; };
	int get_age(){ return age; };
	int get_hunger(){ return hunger; };
	int get_thirsty(){ return thirsty; };
	int get_mood(){ return mood; };
	int get_health(){ return health; };
	int get_step(){ return step; };
	

	void feed(){ hunger = hunger - 3; step = step - 4; money = money - 3; };
	void drink() { thirsty = thirsty - 2; step = step - 3; money = money - 2; };
	void doctor() { step = step - 8; money = money - 5; };
	void touch(int w);                    
	void fun(int w);         
	void work(){ int o = rand() % 4 + 25; money = money + o; step = step - 6; };
	void adventure();
	void emergency(int emg);
	void judge(int emg);
	void p2();

	virtual int get_life(){ return 0; };
	virtual void action(int act, int w, int &emg){}
	




};

void pet::p2()
{
	srand(time(0));
	int i = rand() % 15;
	if (i<3)
		mood = mood - 2;
	else if (i<12)
		mood--;
	else
		mood++;
		hunger = hunger++;
		thirsty = thirsty++;
		age++;
}

void pet::fun(int w)
{
	step = step - 5;
	health = health + 2;
	mood++;
	switch (w)
	{
	case 1:
		mood = mood + 2;
		break;
	case 2:
		hunger++;
		mood++;
		break;
	case 3:
		mood++;
		thirsty++;
		break;
	case 4:
		hunger++;
		thirsty++;
		mood++;
		break;
	}

}

void pet::adventure()
{
	srand(time(0));
	int p = rand() % 5;
	step = step - 6;
	switch (p)
	{

	case 0:
	{
			  cout << "偶遇1只哥布林，成功解决！声望加5，金币加10。" << endl;
			  prestige = prestige + 5;
			  money = money + 10;
			  hunger++;
			  break;
	}
	case 1:
	{
			  cout << "在迷雾森林中捡到一箱金币" << endl;
			  money = money + rand() % 7 + 10;
			  break;
	}
	case 2:
	{
			  cout << "撞见一群哥布林团伙，经过一番苦战获得胜利。声望加15，金币加30" << endl;
			  money = money + 30;
			  prestige = prestige + 15;
			  hunger = hunger + 2;
			  thirsty++;
			  break;
	}
	case 3:
	{
			  cout << "逮到1只落单的哥布林！声望加5，金币加10。" << endl;
			  prestige = prestige + 5;
			  money = money + 10;
			  hunger++;
			  break;
	}
	case 4:
	{
			  cout << "碰到一堆魔兽，惊险逃脱！" << endl;
			  hunger++;
	}
	}

}

void pet::touch(int w)
{
	step = step - 3;
	if (w == 0)
	{
		mood=mood+4;
	
	}
	else if (w == 1 || w == 2)
	{
		mood++;

	}
	else if (w == 3)
	{
		mood--;

	}
	else if (w==4)
	{
		mood = mood - 2;

	}

}

void  pet::judge(int emg)
{
	if (hunger>10 || thirsty>8)
	{
		age = 100;
		cout << "“啊！我前世造的什么孽？“说完，你的宠物倒地不起，可以看出它走的很不安详。" << endl;
	}
	if (hunger>9 && thirsty>7)
	{
		age = 100;
		cout << "“希望我下一世能跟上一个让我吃饱喝足的主人 ”这是你宠物走前的最后一句话。(ー`´ー)" << endl;
	}
	if (health<-9)
	{
		age = 100;
		cout << "当你发现时，你的宠物已经惨死家中。" << endl;
	}
}

void  pet::emergency(int emg)
{
	step = step + 5;
	if (emg==20)
		health--;
	if (hunger == 3)
	{
		
		cout << "主人，我有点饿，好想吃东西。(｀・ω・´)" << endl;
	}
	if (hunger == -4)
	{
		mood--;
		cout << "主人，我吃不下了。(￣.￣)" << endl;
	}
	if (hunger>4)
	{
		mood = mood - 1;
		health--;
		cout << "求求你给我点吃的吧，我快要饿死啦！(￣３￣)" << endl;
	}
	if (hunger<-4)
	{
		mood = mood - 1;
		health--;
		cout << "不能吃了，我快撑死啦！o(╥﹏╥)o" << endl;
	}
	if (thirsty == 3)
	{
		
		cout << "好口渴啊，给水的吧。罒ω罒" << endl;
	}
	if (thirsty == -3)
	{
		
		cout << "主人，我感觉我快喝吐了。(〒︿〒)" << endl;
	}
	if (thirsty>3)
	{
		mood = mood - 1;
		health--;
		cout << " 就算我渴死，渴成干尸，我也不喝你一滴水，哼！╭(╯^╰)╮" << endl;
	}
	if (thirsty<-3)
	{
		mood = mood - 1;
		health--;
		cout << "你的宠物不想和你说话，并向你砸来半盆水。(▼ヘ▼#)" << endl;
	}
	judge(emg);

}

class rabbit :virtual public pet
{
	int life;
public:
	rabbit(int a = 0, int hu = 0, int t = 0, int m = 0, int he = 0, int s = 20, int l = 30, int mon = 50, int p = 0) : pet(a, hu, t, m, he, s, mon,p){ life = l; };
	int get_life(){ return life; };
	virtual void action(int act, int w, int &emg)
	{
		switch (act)
		{
		case 0:
		{
			instruction();
			break; 
		}
		case 1:
		{
			feed();
			break;
		}
		case 2:
		{
			drink();
			break;
		}
		case 3:
		{
			touch(w);
			break; 
		}
		case 4:
		{
			fun(w);
			break; 
		}
		case 5:
		{
				  work();
				  break;
		}
		case 6:
		{
				  adventure();
				  break;
		}
		case 7:
			break;
		
		case 8:
			doctor();
			emg = 0;
		
		}

	};
};

class horse :virtual public pet
{
	int life;
public:
	horse(int a = 0, int hu = 0, int t = 0, int m = 0, int he = 0, int s = 20, int l = 30, int mon = 50, int p = 0) : pet(a, hu, t, m, he, s, mon, p){ life = l; };
	int get_life(){ return life; };
	virtual void action(int act, int w, int &emg)
	{
		switch (act)
		{
		case 0:
		{
				  instruction();
				  break;
		}
		case 1:
		{
				  feed();
				  break;
		}
		case 2:
		{
				  drink();
				  break;
		}
		case 3:
		{
				  touch(w);
				  break;
		}
		case 4:
		{
				  fun(w);
				  break;
		}
		case 5:
		{
				  work();
				  break;
		}
		case 6:
		{
				  adventure();
				  break;
		}
		case 7:
			break;

		case 8:
			doctor();
			emg = 0;

		}

	};
};

class cattle :virtual public pet
{
	int life;
public:
	cattle(int a = 0, int hu = 0, int t = 0, int m = 0, int he = 0, int s = 20, int l = 30, int mon = 50, int p = 0) : pet(a, hu, t, m, he, s, mon, p){ life = l; };
	int get_life(){ return life; };
	virtual void action(int act, int w, int &emg)
	{
		switch (act)
		{
		case 0:
		{
				  instruction();
				  break;
		}
		case 1:
		{
				  feed();
				  break;
		}
		case 2:
		{
				  drink();
				  break;
		}
		case 3:
		{
				  touch(w);
				  break;
		}
		case 4:
		{
				  fun(w);
				  break;
		}
		case 5:
		{
				  work();
				  break;
		}
		case 6:
		{
				  adventure();
				  break;
		}
		case 7:
			break;

		case 8:
			doctor();
			emg = 0;

		}

	};
};

int petshop()
{
	string sel;
	int k = 0;
	cout << "现在有三种宠物可以领养，分别是 【1】小兔子，【2】小马驹，【3】小牛" << endl;
	cout << "请选择你想领养的宠物：";
	while (!k)
	{
		cin >> sel;
		if (sel == "1")
		{
			cout << "你选择的是小兔子" << endl;
			cout << "                             (  (  (                        " << endl;
			cout << "                              \\  )  ) _..-.._               " << endl;
			cout << "                             __)/ ,*,*       *.             " << endl;
			cout << "                           ,*     **     ,--.  *.           " << endl;
			cout << "                         ,*   0        *'    *   \\          " << endl;
			cout << "                        (Y            (           ;**.      " << endl;
			cout << "                         *--.____,     \\          ,  ;      " << endl;
			cout << "                         ((_ ,----* ,---*      _,*_,*       " << endl;
			cout << "                             (((_,- (((______,-*            " << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			k = 1;
		}
		else if (sel == "2")
		{
			cout << "你选择的是小马驹" << endl;
			cout << "                                         ~~%%%%%%%%_,_,           " << endl;
			cout << "                                       ~~%%%%%%%%%-*/./           " << endl;
			cout << "                                     ~~%%%%%%%-*   / *.           " << endl;
			cout << "                                  ~~%%%%%%%%* .     ,--;          " << endl;
			cout << "                                ~~%%%%%%%%*   :       \\O\\         " << endl;
			cout << "                              ~~%%%%%%%%*    :          *.        " << endl;
			cout << "                           ~~%%%%%%%%*       *. -,        *       " << endl;
			cout << "                        ~~%%%%%%%%*          .**-.-        *.     " << endl;
			cout << "                    ~~%%%%%%%%%*           :     *-.     (,;      " << endl;
			cout << "                    ~~%%%%%%%%*             :         *.-\\-.*     " << endl;
			cout << "                    ~~%%%%%%%*              ;                     " << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			k = 2;
		}
		else if (sel == "3")
		{
			cout << "你选择的是小牛" << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			cout << "                               /~~~~/   /~~~~/               " << endl;
			cout << "                               /    /   /    /               " << endl;
			cout << "                                |  |_____|  |                " << endl;
			cout << "                              /~             ~/              " << endl;
			cout << "                     /~~~~~-_|  /~~/    /~~~/  |_-~~~~~\\     " << endl;
			cout << "                     / ==== /| |   O|  |O    | |/ ==== /     " << endl;
			cout << "                      ~-__-~ | |_---+--+----_| | ~-__-~      " << endl;
			cout << "                             |/~             ~/|             " << endl;
			cout << "                             /                 /             " << endl;
			cout << "                            (     O      O      )            " << endl;
			cout << "                              /              ./              " << endl;
			cout << "                               ~-__________-~|               " << endl;
			cout << "                               |   |/__/|    |               " << endl;
			cout << "                               |   |/~~/|    |               " << endl;
			cout << "                               | /~~~~~~~~~/ |               " << endl;
			cout << "                               | |         | |               " << endl;
			cout << "                               | |         | |               " << endl;
			cout << "-------------------------------------------------------------------------------" << endl;
			k = 3;
		}
		else
		{
				   cout << "请输入 1-3之中的数字：" << endl;
				   k = 0;
		}
		
	}
		return k;
}

void instruction()
{
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
	cout << "饲养说明：" << endl;
	cout << "每个时间段作为主人的你新增5点行动点，未用完可以累积到下一时段，初始有20点。" << endl;
	cout << "当行动点相当低时，出现bad end，饲养结束。" << endl;
	cout << "每天有三个时间段，你可以进行8项操作，喂食、喂水、抚摸、玩耍、打工、冒险、不做任何事、去医院。" << endl;
	cout << "行动点对应消耗：喂食4点，喂水3点，抚摸3点，玩耍5点，打工6点，冒险6点，去医院8点。" << endl;
	cout << "选择不做任何事，则跳到下一时间段。" << endl;
	cout << "当饥饿与口渴相当低的时候，或者健康指数相当低的时候，会出现bad end，宠物死亡。" << endl;
	cout << "当宠物年龄到达寿命极限时，出现happy end，宠物寿终正寝。" << endl;
	cout << "PS：不同的天气对宠物的心情和健康又影响。" << endl;
	cout << "在不同天气中进行抚摸玩耍会有特殊情况发生，请注意。" << endl;
	cout << "宠物寿终正寝后，可查看自己是否获得成就" << endl;
	cout << "-------------------------------------------------------------------------------------------------------" << endl;
}

int adopt()
{
	string name;
	string ch1;
	int ch;
	int sel = petshop();
	cout << "请为你的宠物起名：";
	cin >> name;
	cout << "是否显示说明: 1、是  2、否" << endl;
	cout << "请选择:";
	while (1)
	{

		cin >> ch1;
		if (ch1== "1")
		{
			instruction();
			break;
		}
		else if (ch1 == "2")
			return sel;
		else
			cout << "请输入1或2：";
	}
	return sel;
	
}

int weather()                  //天气函数
{
	srand(time(0));
	int w= rand() % 5;
	switch (w)
	{
	case 0:cout << "天气：晴。" << endl; break;
	case 1:cout << "天气：阴。" << endl; break;
	case 2:cout << "天气：小雨。" << endl; break;
	case 3:cout << "天气：暴雨。" << endl; break;
	case 4:cout << "天气：大风。" << endl; break;
	}
	return w;
}

void period(int t)             //时间函数
{
	t = t % 3;
	switch (t)
	{
	case 0:cout << "上午。" << endl; break;
	case 1:cout << "下午。" << endl; break;
	case 2:cout << "晚上。" << endl; break;
	}
};

void raise_judge(int &emg)  //是否依旧生病
{
	if (emg == 20)
		emg = 20;
	else
		emg = rand() % 21;
}

void raise_ill(int emg,int step)
{
	if ((emg - 19) == 1)
		cout << "健康状况：生病" << endl;
	else
		cout << "健康状况：良好" << endl;
	cout << "------------------------------------------------------------------" << endl;
	cout << "当前的行动值为： " << step << endl;
	cout << "请选择你想做的事：" << endl;
	cout << "0、参看说明 1、喂食 2、喂水 3、抚摸 4、逗它玩耍 5、打工 6、冒险 7、不做任何事";
	if ((emg - 19) == 1)
		cout << " 8、看医生。";
	cout << endl << "请选择：";
};

void raise_xh_1(string ac, int &k, int &o)
{
	if (ac == "0")
	{
		k = 0;
		o = 1;
	}
	else if (ac == "1")
	{
		k = 1;
		o = 1;
	}
	else if (ac == "2")
	{
		k = 2;
		o = 1;
	}
	else if (ac == "3")
	{
		k = 3;
		o = 1;
	}
	else if (ac == "4")
	{
		k = 4;
		o = 1;
	}
	else if (ac == "5")
	{
		k = 5;
		o = 1;
	}
	else if (ac == "6")
	{
		k = 6;
		o = 1;
	}
	else if (ac == "7")
	{
		k = 7;
		o = 1;
	}
	else if (ac == "8")
	{
		k = 8;
		o = 1;
	}
	else
		cout << "请输入1-8的数字：" << endl;
}

void raise_xh(string ac,int &k)
{
	int o =0;
	while (!o)
	{
		cin >> ac;
		raise_xh_1(ac, k, o);
		
	}
}

void raise_ach(int mood,int prestige,int money)    //成就
{
	if (mood >= 5 && mood<10)
		cout << "经过你悉心的照顾，你的宠物生活的很开心。恭喜你获得“无微不至”的称号" << endl;
	else if (mood >= 10)
		cout << "经过你悉心的照顾，你的宠物生活的十分开心。恭喜你获得“育宠达人”的称号" << endl;

	if (money >= 200 && money<300)
		cout << "通过这些日子，你成功获得不少财富。恭喜你获得“白手起家”的称号" << endl;
	else if (money >= 300)
		cout << "通过这些日子，你成功获得许多财富。恭喜你获得“宠物大亨”的称号" << endl;
	if (prestige >= 100 && prestige<150)
		cout << "经过不懈努力，你在一定范围内有些声望。恭喜你获得“小有名气”的称号" << endl;
	else if (prestige >= 150)
		cout << "经过不懈努力，你成功声名远播。恭喜你获得“名誉天下”的称号" << endl;
}

void raise1(int sel)
{
	int t, emg=1, date, act,life,w,k,step,age;
	string ac;
	pet *it;                        //动态建立对象，实现领养
	switch (sel)
	{
	case 1:
		it = new rabbit;
		break;
	case 2:
		it = new horse;
		break;
	case 3:
		it = new cattle;
		break;
	}
	life = it->get_life();
	
	
	for (date = 1; date <=life; date++)
	{
		cout << "今天是你领养第" << date << "日" << endl;
		w = weather();
		it->p2();
		for (t = 0; t < 3; t++)
		{
			
			step = it->get_step();
			raise_judge(emg);
			
			period(t);
			it->show();
			raise_ill(emg, step);		  
			raise_xh(ac, k);//循环
			it->action(k, w, emg);
			it->emergency(emg);
			age = it->get_age();
			step = it->get_step();
			cout << "**********************************************************************************" << endl;
			if (age == 100)
			{
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "很遗憾，由于饲养不善，你的宠物已经死亡。" << endl;
				cout << "-------------------------------------------------------------------------------" << endl;
				break;

			}                     //非正常死亡，bad end


			if (step < 0)
			{
				age = 100;
				cout << "-------------------------------------------------------------------------------" << endl;
				cout << "真不幸，宠物的饲养已经让你感到心力交瘁。" << endl;
				cout << "看来你和它共同的生活要就此告一段落了。" << endl;
				cout << "唉，你的修行还未够班啊，继续努力吧。" << endl;
				cout << "-------------------------------------------------------------------------------" << endl;

				break;
			}                     //非正常结束饲养，bad end 

		}

		if (age > life)
			break;
		       
	}
	if (date == life+1)
	{
		cout << "-------------------------------------------------------------------------------" << endl;
		cout << "恭喜，你的宠物在你的照顾下，幸福地过完了它的一生。" << endl;          //正常死亡
		int mood = it->get_mood();
		int money = it->get_money();
		int prestige = it->get_prestige();
		raise_ach(mood, prestige, money);
		
	}
		
			

}

int main()
{
	int choose = 0;
	while (!choose)
	{
		cout << "-------------------------------------------------------------------------" << endl;
		string ch;
		string ch1;
		int sel = adopt();
		cout << "是否开始饲养宠物：1.是   2.否" << endl;

		while (1)
		{
			
			cin >> ch;
			cout << "-----------------------------------------------------------------------" << endl;
			if (ch== "1")
			{
				raise1(sel);
				break;
			}
			else if (ch == "2")
				break;
			else
				cout << "请输入1或2：" << endl;
		}

		cout << "是否继续饲养宠物：1.是   2.否" << endl;
		while (1)
		{
			cin >> ch1;
			if (ch1 == "1")
			{
				choose = 0;
				system("cls");
				break;
			}
			else if (ch1 == "2")
			{
				choose = 1;
				break;
			}
			else
				cout << "请输入1或2：" << endl;
		}
	}
    return 0;
}
	