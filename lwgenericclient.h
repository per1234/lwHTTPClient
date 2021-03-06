#ifndef LWGENERICCLIENT_H
#define LWGENERICCLIENT_H

/*
    乐为物联网客户端基类
    ====================

    这是整个library的基类，其它lib都是在此基类上面通过实现不同的接口而形成。

    由于所有的服务都需要发送数据到服务器,所以基类也实现了IPost接口。



    使用方法：

    创建实例之后，第一步设置好UserKey和GateWay；
    上传数据时，先调用append()方法追加数据，然后统一通过submit()来上传到服务器。



    子类化注意事项
    ==============

    创建此基类的子类的时候，需要注意submit（）方法并没有真正实现上传数据的功能，
    具体实现的代码在子类的uploadValue()方法中。

*/

/*
    版本历史
    ========

    v1.1 @ 2013-11-05    将原来的纯虚方法append()改成实体方法，每个append方法生成相应的key：value JSON对
                         cmdJSON字串的内容为所有的key:value对，不包含http或tcp方式中特定的字符前缀或者后缀
                         例如不含tcp方式中的"&^!"
    v1.0 @ 2013-10-01    创建项目

*/


#include "ipost.h"
#include "debuglog.h"
#include "Arduino.h"


class lwGenericClient : public IPost
{
public:
    lwGenericClient(const char* userkey, const char* gateway)
    {
        active = false;
        cmdJSON=(char*) malloc(9);
        clearCommand();
        lastTime = millis();

        setUserKey(userkey);
        setGateWay(gateway);
    }

    lwGenericClient()
    {
        active =false ;
        cmdJSON=(char*) malloc(9);
        clearCommand();
        lastTime = millis();
    }

    void setUserKey(const char* userkey)
    {
        userKey = userkey;
    }

    void setGateWay(const char* gateway)
    {
        gateWay = gateway;
    }

    virtual  void append(const char* sensor, bool value);
    virtual  void append(const char* sensor, int value);
    virtual  void append(const char* sensor, unsigned int value);
    virtual  void append(const char* sensor, long value);
    virtual  void append(const char* sensor, unsigned long value);
    virtual  void append(const char* sensor, double value,unsigned int digits=2);
    virtual  void append(const char* sensor, const char* value);

    virtual void submit();

protected:
    unsigned int interval;
    unsigned long lastTime;
    const char* userKey;
    const char* gateWay;
    char* cmdJSON;
    bool active; //保存ethernet.begin()返回结果的
    virtual void uploadValue() = 0;
    virtual void clearCommand();
    virtual void appendCommand(const char* cmd);
    //virtual void formatCommand()=0; //submit数据之前调用，修改cmdJSON为相应的命令格式
private:

};

#endif // LWGENERICCLIENT_H
