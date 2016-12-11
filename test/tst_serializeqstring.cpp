#include <QString>
#include <QtTest>
#include <QTemporaryDir>
#include <QtDebug>
#include <fstream>

#include "qarchive.hpp"
#include <boost/serialization/nvp.hpp>

class serializeQstring : public QObject
{
    Q_OBJECT

    QString fileName = "qstring.xml";
    QTemporaryDir dir;
    QString filePath;

    QString testString =  "Qstring with $ome <>";

public:
    serializeQstring();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void save();
    void load();
};

serializeQstring::serializeQstring()
{
    if (dir.isValid()) {
        filePath = QDir(dir.path()).absoluteFilePath(fileName);
    }
    else
        filePath = fileName;
}

void serializeQstring::initTestCase()
{
}

void serializeQstring::cleanupTestCase()
{
}

void serializeQstring::save()
{
    std::ofstream ofs(filePath.toLocal8Bit().constData());
    QVERIFY(ofs.good());
    q_xml_oarchive oa(ofs);
    oa << BOOST_SERIALIZATION_NVP(testString);
    ofs.close();

    QFile file(filePath);
    QVERIFY(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QTextStream in(&file);
    QVERIFY(in.readAll().contains("<testString>Qstring with $ome &lt;&gt;</testString>"));
}

void serializeQstring::load()
{
    std::ifstream ifs(filePath.toLocal8Bit().constData());
    QVERIFY(ifs.good());
    q_xml_iarchive ia(ifs);
    QString str;
    ia >> BOOST_SERIALIZATION_NVP(str);
    QCOMPARE(str, testString);
}

QTEST_APPLESS_MAIN(serializeQstring)

#include "tst_serializeqstring.moc"
