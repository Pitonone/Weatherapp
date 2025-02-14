#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mApiHandler = new ApiHandler;
    connect(ui->mGetWheatherBtn, &QPushButton::clicked, this, &MainWindow::getWeather);
    connect(mApiHandler, &ApiHandler::sendDoneMessage, this, &MainWindow::requestDone);
    connect(mApiHandler, &ApiHandler::sendErrorMessage, this, &MainWindow::showErrorMessage);

    mCountryCodeMap =
    {
        {"Afghanistan", "AF"},
        {"Albania", "AL"},
        {"Algeria", "DZ"},
        {"Andorra", "AD"},
        {"Angola", "AO"},
        {"Antigua and Barbuda", "AG"},
        {"Argentina", "AR"},
        {"Armenia", "AM"},
        {"Australia", "AU"},
        {"Austria", "AT"},
        {"Azerbaijan", "AZ"},
        {"Bahamas", "BS"},
        {"Bahrain", "BH"},
        {"Bangladesh", "BD"},
        {"Barbados", "BB"},
        {"Belarus", "BY"},
        {"Belgium", "BE"},
        {"Belize", "BZ"},
        {"Benin", "BJ"},
        {"Bhutan", "BT"},
        {"Bolivia", "BO"},
        {"Bosnia and Herzegovina", "BA"},
        {"Botswana", "BW"},
        {"Brazil", "BR"},
        {"Brunei Darussalam", "BN"},
        {"Bulgaria", "BG"},
        {"Burkina Faso", "BF"},
        {"Burundi", "BI"},
        {"Cabo Verde", "CV"},
        {"Cambodia", "KH"},
        {"Cameroon", "CM"},
        {"Canada", "CA"},
        {"Central African Republic", "CF"},
        {"Chad", "TD"},
        {"Chile", "CL"},
        {"China", "CN"},
        {"Colombia", "CO"},
        {"Comoros", "KM"},
        {"Congo (Congo-Brazzaville)", "CG"},
        {"Congo, Democratic Republic of the", "CD"},
        {"Costa Rica", "CR"},
        {"Croatia", "HR"},
        {"Cuba", "CU"},
        {"Cyprus", "CY"},
        {"Czechia (Czech Republic)", "CZ"},
        {"Denmark", "DK"},
        {"Djibouti", "DJ"},
        {"Dominica", "DM"},
        {"Dominican Republic", "DO"},
        {"Ecuador", "EC"},
        {"Egypt", "EG"},
        {"El Salvador", "SV"},
        {"Equatorial Guinea", "GQ"},
        {"Eritrea", "ER"},
        {"Estonia", "EE"},
        {"Eswatini (fmr. 'Swaziland')", "SZ"},
        {"Ethiopia", "ET"},
        {"Fiji", "FJ"},
        {"Finland", "FI"},
        {"France", "FR"},
        {"Gabon", "GA"},
        {"Gambia", "GM"},
        {"Georgia", "GE"},
        {"Germany", "DE"},
        {"Ghana", "GH"},
        {"Greece", "GR"},
        {"Grenada", "GD"},
        {"Guatemala", "GT"},
        {"Guinea", "GN"},
        {"Guinea-Bissau", "GW"},
        {"Guyana", "GY"},
        {"Haiti", "HT"},
        {"Honduras", "HN"},
        {"Hungary", "HU"},
        {"Iceland", "IS"},
        {"India", "IN"},
        {"Indonesia", "ID"},
        {"Iran", "IR"},
        {"Iraq", "IQ"},
        {"Ireland", "IE"},
        {"Israel", "IL"},
        {"Italy", "IT"},
        {"Jamaica", "JM"},
        {"Japan", "JP"},
        {"Jordan", "JO"},
        {"Kazakhstan", "KZ"},
        {"Kenya", "KE"},
        {"Kiribati", "KI"},
        {"Korea, North", "KP"},
        {"Korea, South", "KR"},
        {"Kuwait", "KW"},
        {"Kyrgyzstan", "KG"},
        {"Laos", "LA"},
        {"Latvia", "LV"},
        {"Lebanon", "LB"},
        {"Lesotho", "LS"},
        {"Liberia", "LR"},
        {"Libya", "LY"},
        {"Liechtenstein", "LI"},
        {"Lithuania", "LT"},
        {"Luxembourg", "LU"},
        {"Madagascar", "MG"},
        {"Malawi", "MW"},
        {"Malaysia", "MY"},
        {"Maldives", "MV"},
        {"Mali", "ML"},
        {"Malta", "MT"},
        {"Marshall Islands", "MH"},
        {"Mauritania", "MR"},
        {"Mauritius", "MU"},
        {"Mexico", "MX"},
        {"Micronesia", "FM"},
        {"Moldova", "MD"},
        {"Monaco", "MC"},
        {"Mongolia", "MN"},
        {"Montenegro", "ME"},
        {"Morocco", "MA"},
        {"Mozambique", "MZ"},
        {"Myanmar (formerly Burma)", "MM"},
        {"Namibia", "NA"},
        {"Nauru", "NR"},
        {"Nepal", "NP"},
        {"Netherlands", "NL"},
        {"New Zealand", "NZ"},
        {"Nicaragua", "NI"},
        {"Niger", "NE"},
        {"Nigeria", "NG"},
        {"North Macedonia", "MK"},
        {"Norway", "NO"},
        {"Oman", "OM"},
        {"Pakistan", "PK"},
        {"Palau", "PW"},
        {"Palestine State", "PS"},
        {"Panama", "PA"},
        {"Papua New Guinea", "PG"},
        {"Paraguay", "PY"},
        {"Peru", "PE"},
        {"Philippines", "PH"},
        {"Poland", "PL"},
        {"Portugal", "PT"},
        {"Qatar", "QA"},
        {"Romania", "RO"},
        {"Russia", "RU"},
        {"Rwanda", "RW"},
        {"Saint Kitts and Nevis", "KN"},
        {"Saint Lucia", "LC"},
        {"Saint Vincent and the Grenadines", "VC"},
        {"Samoa", "WS"},
        {"San Marino", "SM"},
        {"Sao Tome and Principe", "ST"},
        {"Saudi Arabia", "SA"},
        {"Senegal", "SN"},
        {"Serbia", "RS"},
        {"Seychelles", "SC"},
        {"Sierra Leone", "SL"},
        {"Singapore", "SG"},
        {"Slovakia", "SK"},
        {"Slovenia", "SI"},
        {"Solomon Islands", "SB"},
        {"Somalia", "SO"},
        {"South Africa", "ZA"},
        {"South Sudan", "SS"},
        {"Spain", "ES"},
        {"Sri Lanka", "LK"},
        {"Sudan", "SD"},
        {"Suriname", "SR"},
        {"Sweden", "SE"},
        {"Switzerland", "CH"},
        {"Syria", "SY"},
        {"Tajikistan", "TJ"},
        {"Tanzania", "TZ"},
        {"Thailand", "TH"},
        {"Timor-Leste", "TL"},
        {"Togo", "TG"},
        {"Tonga", "TO"},
        {"Trinidad and Tobago", "TT"},
        {"Tunisia", "TN"},
        {"Turkey", "TR"},
        {"Turkmenistan", "TM"},
        {"Tuvalu", "TV"},
        {"Uganda", "UG"},
        {"Ukraine", "UA"},
        {"United Arab Emirates", "AE"},
        {"United Kingdom", "GB"},
        {"United States of America", "US"},
        {"Uruguay", "UY"},
        {"Uzbekistan", "UZ"},
        {"Vanuatu", "VU"},
        {"Vatican City", "VA"},
        {"Venezuela", "VE"},
        {"Vietnam", "VN"},
        {"Yemen", "YE"},
        {"Zambia", "ZM"},
        {"Zimbabwe", "ZW"}

    };

    for (const QString &countryName : mCountryCodeMap.keys())
    {
        ui->mCountryBox->addItem(countryName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::requestDone(ApiHandler::Data pData)
{
   ui->mWethaerDataLabel->setText(pData.mWeather);
   ui->mTempDataLAbel->setText(pData.mTemperature);
   ui->mCountryBox->clearEditText();
}

void MainWindow::showErrorMessage(QString pErrorMessage)
{
    QMessageBox::critical(this, "Error", pErrorMessage);
}

void MainWindow::getWeather()
{
    if (ui->mCityLineEdit->text() == "")
    {
        showErrorMessage("City name cannot be empty");
    }
    else
    {
        mApiHandler->getData(ui->mCityLineEdit->text(), mCountryCodeMap.value(ui->mCountryBox->currentText()));
    }
}

