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
    
    //�����ַ�Ƶ�� 
	unsigned char ch[10050];
	long long len = 0;
	long long big = 0;
	long long now = 0;
	in.seekg(0,ios::end);
	len = in.tellg();
	in.seekg(0,ios::beg);
	while(!in.eof())
	{
	   //��ȡ����ʹ��uchar ʹ��uchar��Ϊkey 
	   // ch��Ϊ������ʹ�� 
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
	cout<<"�������"<<endl;
	m[500]++; //�����ı�ʶ���� 
	
	//�洢Ƶ�� 
	for(auto i:m)
	{
		//ת��Ϊuint�洢 secondΪ���� 
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
		m2[now->getval()] = s; //val Ϊԭ�ļ����� 
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
	if(buildtree(s)) ;//���� 
	else
	{
		cout<<"ѹ��ʧ��"<<endl;
		return;
	} 
	if(code("",head)) ;//���� 
	else
	{
		cout<<"ѹ��ʧ��"<<endl;
		return;
	}
	ifstream in(s,ios_base::binary);
	ofstream out(s2,ios_base::trunc|ios_base::binary);
	if(!out) cout<<"can not open the file text"<<endl;
	else if(!in) cout<<"can not open the file in"<<endl;
	else
	{
		
		
		
		//д���׺ 
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
		
		
		
		//д������������� 
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
		*int ���� 
		*uint(uchar) keyֵ  ԭ�ļ����� 
		*int val���� 
		*string(char) valֵ  ��Ӧ��01�ַ��� 
		*/
		//��ԭ������ѹ�� 
		//����ת��Ϊλ��ʹ��unsigned long�洢 
		
		
		
		//��ԭ����ѹ�� 
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
		
		//д�������ʶ��
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
		cout<<"����ɹ�"<<endl;
	}
	out.close();
	in.close();
	cout<<"zip complete"<<endl;
	/*ѹ������ 
	��׺ 
	
	����������Ҷ�ӽڵ��� n
	
	n�� 
	key(uint / ucahr)ֵ ԭ�ļ�������
	����(int)ֵ 01�ַ����ĳ��� 
	valֵ(char) ԭ�ļ����ݶ�Ӧ�Ĺ���������ֵ����01�ַ���
	
	ԭ���ݾ������������� (ulong)
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
	//��ԭ��׺ 
	
	ofstream out(to,ios_base::trunc|ios_base::binary);
	int num;
	in.read((char*)&num,sizeof(int));
	//cout<<num<<endl;
	//��ԭ�������� 
	/*
		*int ���� 
		*uint(uchar) keyֵ ԭ�ļ����� 
		*int val���� 
		*string(char) valֵ 
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
	//���� 
	cout<<"��ʼ����"<<endl;
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
