#include "ocr.h"
#include "qdatetime.h"
#define OCR_IMG_SAVE_PATH  "/home/karali/image/OCR/"
#define TESSDATA_PATH "/home/karali/OCRExample/testdata"  // change the path

Ocr::Ocr(QObject *parent) : QObject(parent)
{

    ocr_api = new tesseract::TessBaseAPI();
    ocr_api->Init(TESSDATA_PATH, "tur");

}

Ocr::~Ocr()
{
    delete ocr_api;
}

void Ocr::getText(QString &text, Mat &image)
{
    QString deneme = OCR_IMG_SAVE_PATH;
    QString as = QDateTime::currentDateTime().toString("dd-MMM-yy-hh-mm-ss-zzz000000A");
    deneme = deneme + "karali"+as+".png";
    const QString deneme2 = deneme;
    imwrite(deneme2.toStdString(),image);

    qDebug()<<"deneme--"<<text;
    qDebug()<<"getText-OCR";
    ocr_api->SetImage(image.data, image.cols, image.rows, 3, image.step);
    Mat imGray;
    cvtColor(image, imGray, COLOR_BGR2GRAY);
    setDefault();
    char *ocrResult = ocr_api->GetUTF8Text();
    qDebug()<<&ocrResult;
    std::string str(ocrResult);
    text = QString::fromUtf8(str.c_str());
    text = text.trimmed();
    text = text.simplified();
    text = removeSpecialChar(text);

     qDebug()<<"deneme--2"<<text;

    // get initial referance pixel value!!

    for (int i=0;i<(int)(sizeof(database)/sizeof(database[0])); i++){
        if(text.contains(database[i],Qt::CaseInsensitive))
        {
            QByteArray ba = text.toLocal8Bit();
            const char *c = ba.data();
            double ratio = rapidfuzz::fuzz::partial_ratio(c,database[i]);
            qDebug() << "partial ratio: " << ratio;
            qDebug() << text;


//            int id = Singleton::getIns().getProductId("exit");
//            Singleton::getIns().setProductEstimate(id, "GNCM", text);

//            if(Singleton::getIns().is_BC && Singleton::getIns().is_OCR)
//            {
//              Singleton::getIns().setKeyContent(LSCN, database[i]);
//            }
//            if(!(Singleton::getIns().is_OCR && Singleton::getIns().is_BC))
//            {
//              Singleton::getIns().setKeyContent(GCAM, database[i]);
//            }

//            // emitler kalkacak
//            //emit redText(database[i]);

//            Singleton::getIns().printContent();

        }

    }
    //mutex.unlock();
}

void Ocr::setDefault()
{
    ocr_api->SetPageSegMode(tesseract::PSM_AUTO);
    ocr_api->SetVariable("lstm_choice_mode", "2");
    ocr_api->SetSourceResolution(600);
    ocr_api->Recognize(0);
}

QString Ocr::removeSpecialChar(QString text)
{
    QString fill_char = " ";
    text = text.simplified();
    text = text.replace(("!"), fill_char);
    text = text.replace(("@"), fill_char);
    text = text.replace(("#"), fill_char);
    text = text.replace(("$"), fill_char);
    text = text.replace(("%"), fill_char);
    text = text.replace(("^"), fill_char);
    text = text.replace(("&"), fill_char);
    text = text.replace(("*"), fill_char);
    text = text.replace(("("), fill_char);
    text = text.replace((")"), fill_char);
    text = text.replace(("_"), fill_char);
    text = text.replace(("="), fill_char);
    text = text.replace(("+"), fill_char);
    text = text.replace(("-"), fill_char);
    text = text.replace((";"), fill_char);
    text = text.replace((","), fill_char);
    text = text.replace(("'"), fill_char);
    text = text.replace(("\""), fill_char);
    text = text.replace(("/"), fill_char);
    text = text.replace(("<"), fill_char);
    text = text.replace((">"), fill_char);
    text = text.replace(("?"), fill_char);
    text = text.replace(("["), fill_char);
    text = text.replace(("]"), fill_char);
    text = text.replace(("{"), fill_char);
    text = text.replace(("}"), fill_char);
    text = text.replace(("\n"), fill_char);
    text = text.replace((":"), fill_char);
    text = text.replace(("|"), fill_char);
    text = text.replace(("—"), fill_char);
    text = text.replace(("\""), fill_char);
    text = text.replace(("”"), fill_char);
    text = text.replace(("“"), fill_char);
    text = text.replace(("©"), fill_char);
    text = text.replace(("."), fill_char);
    text = text.replace(("€"), fill_char);
    text = text.replace(("€"), fill_char);
    text = text.replace(("\t"), fill_char);
    text = text.replace(("\r"), fill_char);

    return text;
}

void Ocr::setResolution(int ppi)
{
    ocr_api->SetSourceResolution(ppi);
}
