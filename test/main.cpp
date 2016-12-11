#include <QtTest/QTest>
//#include "tst_serializeqstring.h"
//QTEST_APPLESS_MAIN( QtQuickSampleApplicationTest )


#include <QStringList>
#include <QtTest>
#include <QTemporaryDir>
#include <QtDebug>
#include <fstream>

#include "qarchive.hpp"
#include <boost/serialization/nvp.hpp>

class serializeQstringList : public QObject
{
    Q_OBJECT

    QString fileName = "qstringList.xml";
    QTemporaryDir dir;
    QString filePath;

    QStringList testStringList;

public:
    serializeQstringList();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void save();
    void load();
};

serializeQstringList::serializeQstringList()
{
    testStringList << "Qstring with $ome <>";
    testStringList << "Another Qstring with $ome <>";
    testStringList << "QString with ąłóęćź";

    if (dir.isValid()) {
        filePath = QDir(dir.path()).absoluteFilePath(fileName);
    }
    else
        filePath = fileName;
}

void serializeQstringList::initTestCase()
{
}

void serializeQstringList::cleanupTestCase()
{
}

void serializeQstringList::save()
{
    std::ofstream ofs(filePath.toLocal8Bit().constData());
    QVERIFY(ofs.good());
    q_xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(testStringList);
    ofs.close();

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);
    QVERIFY(in.readAll().contains("<testString>Qstring with $ome &lt;&gt;</testString>"));
}

void serializeQstringList::load()
{
    std::ifstream ifs(filePath.toLocal8Bit().constData());
    QVERIFY(ifs.good());
    q_xml_iarchive ia(ifs);
    QStringList stringList;
    ia >> BOOST_SERIALIZATION_NVP(stringList);
    QCOMPARE(stringList, testStringList);
}

QTEST_APPLESS_MAIN(serializeQstringList)

#include "main.moc"
