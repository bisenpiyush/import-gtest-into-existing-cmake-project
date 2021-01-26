/*
 * SampleClass.h
 *
 *  Created on: 22-Jan-2021
 *      Author: piyush-bisen
 */

#ifndef INCLUDE_SAMPLECLASS_H_
#define INCLUDE_SAMPLECLASS_H_

#include <QObject>
#include <QDebug>
class SampleClass:public QObject{
    Q_OBJECT
public:
    explicit SampleClass(){};
    virtual ~SampleClass(){};
    void print(){
        qDebug()<< "---printing in progress----";
    }
};



#endif /* INCLUDE_SAMPLECLASS_H_ */
