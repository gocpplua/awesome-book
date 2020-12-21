// 5.1.1 �̴߳���
// !!! VSCODE ʹ��mingw64 g++����ʧ�ܣ�error: 'thread' is not a member of 'std'����ʹ��cl.exe ����ɹ�����
#include<iostream>
#include<thread>
#include<future>
using namespace std;

void func()
{
    printf("%s\n", __FUNCTION__);
}

void func1(int i)
{
    printf("%s:%d\n", __FUNCTION__, i);
}

void func2(int i)
{
    printf("%s:%d\n", __FUNCTION__, i);
}

std::vector<std::shared_ptr<std::thread>> g_list;
void funcg()
{
    printf("%s\n", __FUNCTION__);
}
void createthread(){
    g_list.push_back(std::make_shared<std::thread>(funcg));
}

int main()
{
    std::thread t(func);
    t.join(); // �ȴ��������̶߳����func����ִ�����

    std::thread t1(func1, 1);
    t1.detach(); // �̺߳��̶߳���/�̺߳������룬����main����ִ�����ˣ������̺߳�����û��ִ�У������п���func1û�д�ӡ

    std::thread t2(func2, 2);
    printf("%s\n", "========craete t2========");
    std::thread t3(std::move(t2)); // t3 is now running func2(). t2 is no longer a thread

    // �˴�����t2 not joinable��������ִ��t2.join()�����߳�ֱ�ӿ�ס�ˣ���������
    if (t2.joinable()){
        printf("t2 joinable\n");
    }
    else{
        printf("t2 not joinable\n"); 
    }
    

    printf("%s\n", "========create t3========"); // ����ʹ��cout���ܵ��´�ӡ���ң���Ϊprintf���̰߳�ȫ�ģ�Ҳ�����Լ������߳�ͬ���Ĵ���,����cout�����̰߳�ȫ�ģ�Ҫ���Լ�ȥ�߳�ͬ�����Ƚ��鷳 ��
    //t2.join(); // !!! ���߳̿�ס��������ӡ����ִ��
    printf("%s\n", "=========t2 join=========");
    t3.join();
    printf("%s\n", "=========t3 join=========");

    createthread();
    for(const auto& val : g_list){
        val->join();
    }

    return 0;
}