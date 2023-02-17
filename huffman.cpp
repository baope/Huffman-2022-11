#include"Huffman.h"
#define jiasu ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
tree::tree(tree* right,tree* left,unsigned int val,int num)
{
	this->num = num;
	this->val = val;
	this->left = left;
	this->right = right;
}
tree* tree::getleft()
{
	return this->left;
}
int tree::getnum()
{
	return this->num;
}
tree* tree::getright()
{
	return this->right;
}
unsigned int tree::getval()
{
	return this->val;
}
void huffman::my_print(int len ,int now)
{
	double p = now * 10.0 / len;
	int u = p;
	printf("\r[");
	for(int i=1;i<=u;i++)
	{
		if(i==5) printf("%.6lf",p*10); //cout<<setiosflags(ios::fixed)<<setprecision(6)<<p*10<<"%";
		else printf("=");
	}
	for(int i = u+1;i<10;i++)
	{
		if(i==5) printf("%.6lf",p*10); //cout<<setiosflags(ios::fixed)<<setprecision(6)<<p*10<<"%";
		else printf("=");
	}
	printf("]");
}
void huffman::url(string &s)
{
	int len = s.length();
	string s2 = "";
	for(int i = 0 ;i<len;i++)
	{
		if(s[i] == '\\')
		{
			s2+='\\';
		}
		s2+=s[i];
	}
	s = s2;
}
int huffman::buildtree(string s)
{
	ifstream in(s,ios_base::binary|ios::in);
	if(!in.good())
    {
        cout<<"Cannot open the file "<<s<<endl;
        return 0;
    }
    
    //读入字符频率 
	unsigned char ch[10050];
	long long len = 0;
	long long big = 0;
	long long now = 0;
	in.seekg(0,ios::end);
	len = in.tellg();
	in.seekg(0,ios::beg);
	while(!in.eof())
	{
	   //读取数据使用uchar 使用uchar做为key 
	   // ch作为缓冲区使用 
	    if(now+10000<=len) big =9999,now+=10000;
	    else big =len - now,now = len;
		in.read((char*)&ch,sizeof(unsigned char)*10000); 
	    for(int i=0;i<=big;i++)
	    {
			m[ch[i]]++;
		}
		my_print(len,now);
		if(now == len) break;
	}
	cout<<endl;
	cout<<"读入完成"<<endl;
	m[500]++; //结束的标识符号 
	
	//存储频率 
	for(auto i:m)
	{
		//转化为uint存储 second为数量 
		tree *t = new tree(NULL,NULL,i.first,i.second);
		q.push(t);
		//cout<<t->getval()<<" "<<t->getnum()<<endl;
	}
	char no='0';
	while(q.size()>1)
	{
		tree *t1 = q.top();
		q.pop();
		tree *t2 = q.top();
		q.pop();
		tree *t3 = new tree(t1,t2,0,t1->getnum()+t2->getnum());
		q.push(t3);
		//cout<<t1->getnum()<<" "<<t1->getval()<<endl;
	}
	head = q.top();
	q.pop();
	in.close();
	//cout<<head->getnum()<<endl;
	return 1;
}
int huffman::code(string s,tree *now)
{
	if(now==NULL) return 0;
	if(now->getright()==NULL&&now->getleft()==NULL)
	{
		m2[now->getval()] = s; //val 为原文件内容 
		//cout<<now->getval()<<" "<<s<<endl;
	}
	code(s+'1',now->getright());
	code(s+'0',now->getleft());
	return 1;
}
void huffman::zip(string s,string s2)
{
	url(s);
	url(s2);
	if(buildtree(s)) ;//建树 
	else
	{
		cout<<"压缩失败"<<endl;
		return;
	} 
	if(code("",head)) ;//编码 
	else
	{
		cout<<"压缩失败"<<endl;
		return;
	}
	ifstream in(s,ios_base::binary);
	ofstream out(s2,ios_base::trunc|ios_base::binary);
	if(!out) cout<<"can not open the file text"<<endl;
	else if(!in) cout<<"can not open the file in"<<endl;
	else
	{
		
		
		
		//写入后缀 
		char last[10000];
		int ty=0;
		for(int i=0;i<s.length();i++)
		{
			if(s[i]=='.')
			{	
				i++;
				while(i<s.length())
				{
					last[ty] = s[i];
					ty++;
					i++;
				}
			}
		}
		out.write((char*)&ty,sizeof(int));
		out.write((char*)&last,sizeof(char)*ty);
		
		
		
		//写入哈夫曼树数据 
		int num= m2.size();
		out.write((char*)&num,sizeof(int));
		for(auto i : m2)
		{
			char c[10000];
			strcpy(c,i.second.c_str());
			out.write((char*)&i.first,sizeof(unsigned int));
			int len = i.second.length();
			out.write((char*)&len,sizeof(int));
			out.write((char*)&c,sizeof(char)*len);
		}
		bitset<32> b;
		int sum=0;
		/*
		*int 数量 
		*uint(uchar) key值  原文件内容 
		*int val长度 
		*string(char) val值  对应的01字符串 
		*/
		//将原有数据压缩 
		//将其转化为位后使用unsigned long存储 
		
		
		
		//将原内容压缩 
		char buffer[105000];
		long long len = 0;
		long long big = 0;
		long long now = in.tellg();
		in.seekg(0,ios::end);
		len = in.tellg();
		in.seekg(now,ios::beg);
		while(true)
		{
		    if(now+100000<=len) big =99999,now+=100000;
		    else big =len - now,now = len;
			in.read((char*)&buffer,sizeof(unsigned char)*100000);
			
			 for(int i=0;i<=big;i++)
	   		 {
				unsigned char c = buffer[i];
				c = (unsigned int) c;
				const char *d = m2[c].c_str();
				int len_bit = m2[c].length();
				for(int g =0;g<len_bit;g++)
				{
					char i = d[g];
					if(i=='1')
					{
						b.set(sum,true);
						//cout<<1;
					}
					else
					{
						b.set(sum,false);
						//cout<<0;
					}
					sum++;
					if(sum>=8)
					{
						char ul =b.to_ulong();
						out.write((char*)&ul,sizeof(char));
						if(out.fail()) cout<<"error"<<endl;
						b.reset();
						sum=0;
					}
				}
			}
			my_print(len,now);
			if(in.eof()||now==len) break;
		}
		cout<<endl; 
		
		//写入结束标识符
		const char *d = m2[500].c_str();
		int len_bit = m2[500].length();
		for(int g =0;g<len_bit;g++)
		{
			char i = d[g];
			if(i=='1')
			{
				b.set(sum,true);
			}
			else
			{
				b.set(sum,false);
			}
			sum++;
			if(sum>=8)
			{
				char ul =b.to_ulong();
				out.write((char*)&ul,sizeof(char));
				if(out.fail()) cout<<"error"<<endl;
				b.reset();
				sum=0;
			}
		}
		if(sum>0)
		{
			char ul =b.to_ulong();
			out.write((char*)&ul,sizeof(char));
			if(out.fail()) cout<<"error"<<endl;
			b.reset();
			sum=0;
		}
		cout<<"编码成功"<<endl;
	}
	out.close();
	in.close();
	cout<<"zip complete"<<endl;
	/*压缩内容 
	后缀 
	
	哈夫曼树的叶子节点数 n
	
	n个 
	key(uint / ucahr)值 原文件的内容
	长度(int)值 01字符串的长度 
	val值(char) 原文件内容对应的哈夫曼编码值，即01字符串
	
	原内容经过编码后的内容 (ulong)
	*/
}
void huffman::unzip(string s , string to)
{
	url(s);
	map<string,unsigned int> search;
	ifstream in(s,ios_base::binary);
	
	if(to == "")
	{
		for(int i=0;i<s.length();i++)
		{
			if(s[i] == '.') break;
			to+=s[i];
		}
		to+='.';
		int ty;
		char last[1000];
		in.read((char*)&ty,sizeof(int));
		in.read((char*)&last,sizeof(char)*ty);
		for(int i=0;i<ty;i++)
		{
			to+=last[i];
		}
	}
	else
	{
		int ty;
		char last[1000];
		in.read((char*)&ty,sizeof(int));
		in.read((char*)&last,sizeof(char)*ty);
	}
	//还原后缀 
	
	ofstream out(to,ios_base::trunc|ios_base::binary);
	int num;
	in.read((char*)&num,sizeof(int));
	//cout<<num<<endl;
	//还原哈夫曼树 
	/*
		*int 数量 
		*uint(uchar) key值 原文件内容 
		*int val长度 
		*string(char) val值 
	*/
	for(int i=1;i<=num;i++)
	{
		unsigned int t;
		int sum;
		string s="";
		in.read((char*)&t,sizeof(unsigned int)); 
		//cout<<t<<endl;
		in.read((char*)&sum,sizeof(int));
		//cout<<sum<<endl;
		for(int g=1;g<=sum;g++)
		{
			char u;
			in.read((char*)&u,sizeof(char));
			s+=u;
		}
		//cout<<s<<endl;
		search[s] = t;
	}
	string e ="";
	//解码 
	cout<<"开始解码"<<endl;
	unsigned long buffer[100500];
	unsigned char uchar[1000050];
	long long ucharp = 0;
	long long len = 0;
	long long big = 0;
	long long now = in.tellg();
	in.seekg(0,ios::end);
	len = in.tellg();
	in.seekg(now,ios::beg);
	while(true)
	{
	    if(now+400000<=len) big =99999,now+=100000*4;
	    else big =len - now,now = len;
		in.read((char*)&buffer,sizeof(unsigned long)*100000); 
	    for(int g=0;g<=big;g++)
	    {
	    	unsigned long ul = buffer[g];
	    	for(int i=0;i<=31;i++)
			{
				bool p = ul&1;
				ul= ul>>1;
				if(p==1)
					e+="1";
				else 
					e+="0";
				if(search.count(e))
				{
					if(search[e] == 500) break;
					//out<<(unsigned char)search[e];
					uchar[ucharp] = search[e];
					ucharp++;
					if(ucharp == 1000000)
					{
						out.write((char*)uchar,sizeof(unsigned char)*1000000);
						ucharp = 0 ;
						my_print(len,now);
					}
					e="";
				}
			}
		}
		if(in.eof()||now==len) break;
	}
	if(ucharp!=0)
	{
		out.write((char*)uchar,sizeof(unsigned char)*(ucharp-1));
		my_print(len,now);
	}
	cout<<endl; 
	cout<<"unzip complete"<<endl;
}
