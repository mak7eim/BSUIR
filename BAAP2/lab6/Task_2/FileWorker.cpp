#include "FileWorker.h"

FileWorker::FileWorker(QTextBrowser* browser)
    : outputStream(&outputText)
{
    output = browser;
    structDialog = new StructInputDialog(nullptr, &w);
}

void FileWorker::CreateNonExistingFiles()
{
    for (auto fileName : files)
    {
        QFile file(fileName);
        if (!file.exists())
        {
            if (!file.open(QIODevice::WriteOnly))
            {
                QMessageBox::warning(nullptr, QMessageBox::tr("File Creation"), "Failed to create file: " + fileName, QMessageBox::Ok);
                return;
            }
            file.close();
        }
    }
}

void FileWorker::SaveTextToFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        QString text = QInputDialog::getText(nullptr, QInputDialog::tr("Input"), "Enter a paragraph of text:");
        for (int i = 0; i < text.length(); ++i)
        {
            fileStream << text[i];
        }
        file.close();
    }
}

void FileWorker::LoadTextFromFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        while (!fileStream.atEnd())
        {
            QChar c;
            fileStream >> c;
            outputStream << c;
        }
        file.close();
    }
    output->setText(outputText);
    outputText.clear();
}

void FileWorker::SaveArrayToFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        int size = QInputDialog::getInt(nullptr, QInputDialog::tr("Array creation"), "Enter number of array elements:");
        double d;

        for (int i = 0; i < size; ++i)
        {
            d = QInputDialog::getDouble(nullptr, QInputDialog::tr("Input"), "Enter element #" + QString::number(i) + ":");
            fileStream << d << '}';
        }
        file.close();
    }
}

void FileWorker::LoadArrayFromFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        QString data = fileStream.readAll();
        QStringList doubles = data.split("}", Qt::SkipEmptyParts);
        for (auto d : doubles)
        {
            outputStream << d << " ";
        }
        file.close();
    }
    output->setText(outputText);
    outputText.clear();
}

void FileWorker::SaveStructToFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        structDialog->setModal(Qt::ApplicationModal);
        structDialog->show();

        while (structDialog->isVisible())
        {
            QCoreApplication::processEvents();
        }

        QString brandNameStr;
        for (int i = 0; i < w.MAX_NAME_SIZE && w.brandName[i] != QChar('\0'); ++i)
        {
            brandNameStr += w.brandName[i];
        }

        QString text = QString::number(w.numberOfDiamond) + "\n" +
                       QString::number(w.price) + "\n" +
                       w.Model + "\n" +
                       (w.isexpensivewristwatch ? "true" : "false") + "\n" +
                       brandNameStr + "\n";
        for (int i = 0; i < w.MAX_TIME_AMOUNT; ++i)
        {
            text += QString::number(w.worldTimeOffsets[i]) + "\n";
        }
        fileStream << text;
        file.close();
    }
}

void FileWorker::LoadStructsFromFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        while (!fileStream.atEnd())
        {
            QStringList data;
            for (int i = 0; i < 11; ++i)
            {
                QString line = fileStream.readLine();
                if (line.isEmpty() && fileStream.atEnd()) break;
                data.append(line);
            }
            if (data.size() < 11) break;

            WristWatch temp;
            temp.numberOfDiamond = data[0].toInt();
            temp.price = data[1].toDouble();
            temp.Model = data[2].isEmpty() ? QChar(' ') : data[2][0];
            temp.isexpensivewristwatch = data[3] == "true";
            QString name = data[4];
            for (int i = 0; i < name.length() && i < temp.MAX_NAME_SIZE - 1; ++i)
            {
                temp.brandName[i] = name[i];
            }
            temp.brandName[name.length()] = QChar('\0');
            for (int i = 0; i < temp.MAX_TIME_AMOUNT; ++i)
            {
                temp.worldTimeOffsets[i] = data[i + 5].toInt();
            }

            QString brandNameStr;
            for (int i = 0; i < temp.MAX_NAME_SIZE && temp.brandName[i] != QChar('\0'); ++i)
            {
                brandNameStr += temp.brandName[i];
            }

            outputStream << temp.numberOfDiamond << "|" << temp.price << "|" << temp.Model << "|" <<
                (temp.isexpensivewristwatch ? "true" : "false") << "|" << brandNameStr << "|";
            for (int i = 0; i < temp.MAX_TIME_AMOUNT; ++i)
            {
                outputStream << temp.worldTimeOffsets[i] << (i == temp.MAX_TIME_AMOUNT - 1 ? "\n" : "|");
            }
        }
        file.close();
    }
    output->setText(outputText);
    outputText.clear();
}

void FileWorker::SaveStructToBinaryFile(const QString &fileName)
{
    QFile file(fileName);
    QDataStream fileStream(&file);

    if (!file.open(QIODevice::Append))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        structDialog->setModal(Qt::ApplicationModal);
        structDialog->show();

        while (structDialog->isVisible())
        {
            QCoreApplication::processEvents();
        }

        fileStream.writeRawData(reinterpret_cast<const char*>(&w), sizeof(w));
        file.close();
    }
}

void FileWorker::LoadStructsFromBinaryFile(const QString &fileName)
{
    QFile file(fileName);
    QDataStream fileStream(&file);

    if (!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        while (!fileStream.atEnd())
        {
            WristWatch temp;
            fileStream.readRawData(reinterpret_cast<char*>(&temp), sizeof(temp));

            QString brandNameStr;
            for (int i = 0; i < temp.MAX_NAME_SIZE && temp.brandName[i] != QChar('\0'); ++i)
            {
                brandNameStr += temp.brandName[i];
            }

            outputStream << temp.numberOfDiamond << ";" << temp.price << ";" << temp.Model << ";" <<
                (temp.isexpensivewristwatch ? "true" : "false") << ";" << brandNameStr << ";";
            for (int i = 0; i < temp.MAX_TIME_AMOUNT; ++i)
            {
                outputStream << temp.worldTimeOffsets[i] << (i == temp.MAX_TIME_AMOUNT - 1 ? "\n" : ";");
            }
        }
        file.close();
    }
    output->setText(outputText);
    outputText.clear();
}

void FileWorker::SaveSentenceToFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        QString text = QInputDialog::getText(nullptr, QInputDialog::tr("Input"), "Enter a sentence:");
        fileStream << text << "\n";
        file.close();
    }
}

void FileWorker::LoadSentencesFromFile(const QString &fileName)
{
    QFile file(fileName);
    QTextStream fileStream(&file);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(nullptr, QMessageBox::tr("File Open"), "Failed to open file: " + fileName, QMessageBox::Ok);
        return;
    }
    else
    {
        while (!fileStream.atEnd())
        {
            QString s = fileStream.readLine();
            outputStream << s << "\n";
        }
        file.close();
    }
    output->setText(outputText);
    outputText.clear();
}
