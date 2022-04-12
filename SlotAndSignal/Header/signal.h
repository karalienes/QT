#ifndef SIGNAL_H
#define SIGNAL_H

#include <QString>
#include <QObject>


class MyClass: public QObject{

Q_OBJECT

public:
    MyClass( const QString &text, QObject *parent = 0 );
    const QString& text() const;
    int getLengthOfText() const;

public slots:
    void setText( const QString &text );

signals:
    void textChanged( const QString& );

private:
    QString m_text;


};


void MyClass::setText( const QString &text )
{
if( m_text == text )
return;
m_text = text;
emit textChanged( m_text );
}

#endif // SIGNAL_H
