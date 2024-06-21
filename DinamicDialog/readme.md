
Dinamik diyaloglar(dynamic dialogs) çalışma sırasında Qt Designer .ui dosyalarından oluşturulan diyaloglardır.
.ui dosyalarını uic kullanarak C++ koduna dönüştürmek yerine, dosyayı çalışma sırasında QUiLoader sınıfını kullanarak yükleyebiliriz:


QUiLoader uiLoader;
QFile file("sortdialog.ui");
QWidget *sortDialog = uiLoader.load(&file);
if (sortDialog) {
...
}
Çocuk parçacıklara QObject::findChild() kullanarak erişebiliriz: QComboBox
primaryColumnCombo = sortDialog->findChild("primaryColumnCombo");
 if (primaryColumnCombo) { ... }
findChild() fonksiyonu, verilen isim ve tiple eşleşen çocuk nesneleri döndüren bir şablon üye fonksiyondur(template member function).
QUiLoader sınıfı ayrı bir kütüphanede yer alır. Bir Qt uygulamasında QUiLoader’ı kullanabilmek için, uygulamanın .pro dosyasına şu satırı eklememiz gerekir:
CONFIG += uitools
 Dinamik diyaloglar, uygulamayı yeniden derlemeksizin, formun yerleşimini değiştirebilmemizi mümkün kılar.
