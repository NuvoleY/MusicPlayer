#include "music.h"
#include "ui_music.h"
#include<QIcon>
#include<QPixmap>
#include<QPalette>
#include<QDebug>

Music::Music(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Music)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/source/music8.png"));   //窗口图标
    this->setWindowTitle("随听");
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::WindowMinMaxButtonsHint|Qt::WindowSystemMenuHint);  //设置无菜单栏

    //设置背景
    QPixmap pixmap(":/source/colorChange.jpg");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    player=new QMediaPlayer(this);
    playerList=new QMediaPlaylist(this);
    playerList->setPlaybackMode(QMediaPlaylist::Loop);   //默认循环
    ui->pushButtonLoop->setToolTip(tr("顺序播放"));
    player->setPlaylist(playerList);

    ui->verticalSlider_2->hide();   //隐藏音量滑条
    ui->verticalSlider_2->setValue(50);  //初始化音量条位置
    player->setVolume(50);  //初始化音量

    //为右上角按钮添加图标
    ui->pushButtonDestroy->setIcon(QIcon(":/source/XX.png"));
    ui->pushButtonMIN->setIcon(QIcon(":/source/MIN.png"));
    ui->pushButtonTheme->setIcon(QIcon(":/source/cloth3.png"));

    //为右上角按钮添加特效
    ui->pushButtonDestroy->setStyleSheet("QPushButton{border:none;color:rgb(255, 255, 255);}"
                                         "QPushButton:hover{background-color: #FF0000;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonMIN->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonTheme->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8 ;border:none;color:rgb(255, 255, 255);}");

    //为l列表框和歌词框添加样式
    //ui->textEdit->setStyleSheet("QTextEdit{border:none}" "QTextEdit{background-color:transparent}");
    ui->listWidget->setStyleSheet("QListWidget{border:none}" "QListWidget{background-color:transparent}");
    ui->listWidget_2->setStyleSheet("QListWidget{border:none}" "QListWidget{background-color:transparent}");
    ui->listWidget_3->setStyleSheet("QListWidget{border:none}" "QListWidget{background-color:transparent}");

    //为菜单按钮设置属性
    ui->pushButtonHome->setIcon(QIcon(":/source/SongHome.png"));
    ui->pushButtonLike->setIcon(QIcon(":/source/LikeSong.png"));
    ui->pushButtonUsed->setIcon(QIcon(":/source/SongList.png"));
    ui->pushButtonAdd->setIcon(QIcon(":/source/AddSong.png"));

    ui->pushButtonLastSong->setIcon(QIcon(":/source/last.png"));
    ui->pushButtonSuspectSong->setIcon(QIcon(":/source/countinu.png"));
    ui->pushButtonNextSong->setIcon(QIcon(":/source/next.png"));
    ui->pushButtonLiking->setIcon(QIcon(":/source/loverded.png"));
    ui->pushButtonLiking->setEnabled(false);
    ui->pushButtonSuspectSong->setEnabled(false);
    ui->pushButtonLastSong->setEnabled(false);
    ui->pushButtonNextSong->setEnabled(false);
    ui->pushButtonLoop->setIcon(QIcon(":/source/playloop.png"));
    ui->pushButtonVolum->setIcon(QIcon(":/source/void2.png"));

    ui->pushButtonHome->setStyleSheet("QPushButton{border:none;color:rgb(255, 255, 255);}"
                                         "QPushButton:hover{background-color: #bdddf8;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonLike->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonUsed->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8 ;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonAdd->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8 ;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonLastSong->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8 ;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonSuspectSong->setStyleSheet("QPushButton{border:none;color:rgb(255, 255, 255);}"
                                         "QPushButton:hover{background-color: #bdddf8;border:none;color:rgb(255, 255, 255);}");
    ui->pushButtonNextSong->setStyleSheet( "QPushButton{border:none;color:rgb(255, 255, 255);}"
                                           "QPushButton:hover{background-color: #bdddf8;border:none;color:rgb(255, 255, 255);}");

    ui->textEdit->setStyleSheet("QTextEdit{background-color:transparent}"  //设置字体以及背景透明
                                "QTextEdit{border-width:0;border-style:outset}"
                                "QTextEdit{color:rgb(66,66,50)}");
    ui->label_2->setStyleSheet("QLabel{background-color:transparent}"  //设置字体以及背景透明
                                "QLabel{border-width:0;border-style:outset}"
                                "QLabel{color:rgb(66,66,50)}");
    ui->label_2->setText("快来添加喜欢的音乐吧!");

    ui->pushButtonHome->setToolTip(tr("歌曲列表"));
    ui->pushButtonLike->setToolTip(tr("我的喜欢"));
    ui->pushButtonUsed->setToolTip(tr("播放历史"));
    ui->pushButtonAdd->setToolTip(tr("添加歌曲"));

    ui->pushButtonTheme->setToolTip(tr("更换主题"));

    ui->pushButtonLiking->setToolTip(tr("添加喜欢"));
    ui->pushButtonVolum->setToolTip(tr("音量"));

    ui->stackedWidget->setCurrentWidget(ui->page);   //默认页面为歌曲列表
    ui->stackedWidget_2->setCurrentWidget(ui->page_4); //默认为歌词页面

    //双击播放
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(DoubleClicked(QListWidgetItem *))); //双击播放
    connect(ui->listWidget_2,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(DoubleClicked(QListWidgetItem *))); //双击播放
    connect(ui->listWidget_3,SIGNAL(itemDoubleClicked(QListWidgetItem *)),this,SLOT(DoubleClicked(QListWidgetItem *))); //双击播放
    connect(playerList,&QMediaPlaylist::currentIndexChanged,this,&Music::DealPlayer);//更新暂停图标
    connect(playerList,&QMediaPlaylist::currentIndexChanged,this,&Music::JugeLike);//更新暂停图标
    connect(playerList,&QMediaPlaylist::currentIndexChanged,this,&Music::lyrics);//更新歌词
    connect(player,&QMediaPlayer::metaDataAvailableChanged,this,&Music::updateText);//更新文本
    connect(player,&QMediaPlayer::positionChanged,this,&Music::updatePosition);   //更新时间进度
    connect(player,&QMediaPlayer::durationChanged,this,&Music::updateDuration);   //更新进度条
    connect(ui->verticalSlider_2,&QSlider::valueChanged,this,&Music::setVolum);  //更新音量

    QFile file(":/qss/Style.qss");
    file.open(QFile::ReadOnly);
    ui->listWidget->verticalScrollBar()->setStyleSheet(file.readAll());    //垂直滚动条
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFile file2(":/qss/Style2.qss");
    file2.open(QFile::ReadOnly);
    ui->listWidget_2->verticalScrollBar()->setStyleSheet(file2.readAll());    //垂直滚动条
    ui->listWidget_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFile file3(":/qss/Style3.qss");
    file3.open(QFile::ReadOnly);
    ui->listWidget_3->verticalScrollBar()->setStyleSheet(file3.readAll());    //垂直滚动条
    ui->listWidget_3->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QFile fileSlider(":/qss/slider2.qss");   //进度条
    fileSlider.open((QFile::ReadOnly));
    ui->horizontalSlider->setStyleSheet(fileSlider.readAll());

    QFile fileSlider2(":/qss/slider3.qss");   //进度条
    fileSlider2.open((QFile::ReadOnly));
    ui->verticalSlider_2->setStyleSheet(fileSlider2.readAll());

    QFile FiletextEdit(":/qss/texteditfile.qss");
    ui->textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    const QString m_green_SheetStyle = "min-width: 342px; min-height: 342px;max-width:342px;"
                                       " max-height: 342px;border-radius: 171px;background-color:transparent";
    ui->label_3->setStyleSheet(m_green_SheetStyle);
    ui->label_3->setScaledContents(true);

    ui->textEdit->viewport()->installEventFilter(this);
    ui->label_3->installEventFilter(this);

    connect(ui->stackedWidget_2,&QStackedWidget::currentChanged,this,&Music::lrcTimeStart);  //歌词页面改变
    connect(ui->pushButtonTheme,&QPushButton::clicked,this,&Music::LrcPhotoChange);
    connect(ui->pushButtonTheme,&QPushButton::clicked,this,&Music::lrcTimeStart);
    timer=new QTimer(this);
    timer->setInterval(50);
    connect(timer,SIGNAL(timeout()),this,SLOT(LrcPageChange()));
}

Music::~Music()
{
    delete ui;
}

void Music::lrcTimeStart()   //歌词页面
{
    angle=0;
    if(ui->stackedWidget_2->currentWidget()==ui->page_5)
    {
        pix=QPixmap(LrcPhoto);
        //ui->label_3->setScaledContents(true);
        ui->label_3->setPixmap(pix);
        if(isSuspect==false)
        {
            timer->start();
        }
    }
    else
    {
        timer->stop();   //图片停止旋转
    }
}

void Music::LrcPhotoChange()    //歌词图片改变
{
    switch (ThemeNum) {     //根据当前主题切换图片
    case 1:
        LrcPhoto=":/source/911.png";
        break;
    case 2:
        LrcPhoto=":/source/912.png";
        break;
    case 3:
        LrcPhoto=":/source/913.png";
        break;
    }
}

void Music::LrcPageChange()   //图片旋转
{
    angle+=1;
    angle%=360;
    QMatrix matrix;
    matrix.rotate(angle);
    QPixmap rpix;
    rpix=pix.transformed(matrix);
    ui->label_3->setPixmap(rpix);
}

bool Music::eventFilter(QObject* object, QEvent* event)    //事件过滤  根据点击位置切换歌词页面
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        if(object==ui->textEdit->viewport())
        {
            ui->stackedWidget_2->setCurrentWidget(ui->page_5);
        }
        else if(object==ui->label_3)
        {
            ui->stackedWidget_2->setCurrentWidget(ui->page_4);
        }
        return false;        //继续往下执行
    }
    return false;     //继续往下执行
}


void Music::on_pushButtonDestroy_clicked()   //关闭窗口
{
    playerList->clear();
    close();
}

void Music::on_pushButtonMIN_clicked()   //最小化
{
    showMinimized();
}

void Music::on_pushButtonTheme_clicked()   //更换主题
{
    QString ThemePath;  //主题背景路径
    QString buttonIco;  //按钮图标路径
    if(ThemeNum==1)
    {
        ThemePath=":/source/colorChange2.jpg";   //主题图片
        buttonIco=":/source/cloth2.png";      //主题按钮图标
        ThemeNum=2;
    }
    else if(ThemeNum==2)
    {
        ThemePath=":/source/colorVarious2.jfif";
        buttonIco=":/source/cloth.png";
        ThemeNum=3;
    }
    else if(ThemeNum==3)
    {
        ThemePath=":/source/colorChange.jpg";
        buttonIco=":/source/cloth3.png";
        ThemeNum=1;
    }
    QPixmap pixmap(ThemePath);
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this->setPalette(palette);

    ui->pushButtonTheme->setIcon(QIcon(buttonIco));
}

void Music::on_pushButtonHome_clicked()  //播放列表
{
    ui->stackedWidget->setCurrentWidget(ui->page);
}

void Music::on_pushButtonLike_clicked()  //我的喜欢
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}

void Music::on_pushButtonUsed_clicked()  //播放历史
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

//窗口移动 //窗口移动 //窗口移动 //窗口移动 //窗口移动
void Music::mousePressEvent(QMouseEvent *event)  //鼠标按下
{
    if(volumPressed)   //音量键被按下
    {
        ui->verticalSlider_2->hide();
        volumPressed=false;
    }

    mousePosition=event->pos();
    if(mousePosition.x()<=0)    //位置横坐标小于0
        return;
    if(mousePosition.x()>=this->width())  //位置大于窗口宽
        return;
    if(mousePosition.y()<=0)    //位置纵坐标小于零
        return;
    if(mousePosition.y()>=this->height())  //位置纵坐标大于窗口高
        return;
    mouseIsPressd=true;
}

void Music::mouseMoveEvent(QMouseEvent *event)  //鼠标移动
{
    if(mouseIsPressd)
    {
        QPoint DialogMove=event->globalPos()-mousePosition;
        move(DialogMove);
    }
}

void Music::mouseReleseEvent(QMouseEvent *)  //鼠标松开
{
    mouseIsPressd=false;
}

void Music::on_pushButtonSuspectSong_clicked()  //暂停按钮
{
    if(isSuspect==true)
    {
        ui->pushButtonSuspectSong->setIcon(QIcon(":/source/countinued.png"));
        player->play();
        isSuspect=false;
        if(ui->stackedWidget_2->currentWidget()==ui->page_5)
        {
            if(!timer->isActive())
            {
                timer->start();     //如果播放  图片旋转
            }
        }
    }
    else if(isSuspect==false)
    {
        ui->pushButtonSuspectSong->setIcon(QIcon(":/source/countinu.png"));
        player->pause();
        isSuspect=true;
        if(timer->isActive())
        {
            timer->stop();     //如果暂停  图片停止旋转
        }
    }
}

void Music::DoubleClicked(QListWidgetItem * item)  //双击播放
{
    QString ItemName=item->text();
    for(QMap<QString,int>::iterator i=SongNameMap.begin();i!=SongNameMap.end();i++)
    {
        if(ItemName==i.key())
        {
            playerList->setCurrentIndex(i.value());
            if(ui->stackedWidget_2->currentWidget()==ui->page_5)
            {
                if(!timer->isActive())
                {
                    timer->start();      //双击播放 图片旋转
                }
            }
        }
    }
}

void Music::DealPlayer()   //处理暂停图标  双击播放时  添加到历史 处理喜欢标识
{
    BarInitPosition=0;  //歌词条初始位置

    isSuspect=false;
    ui->pushButtonSuspectSong->setIcon(QIcon(":/source/countinued.png"));  //调整暂停播放按钮
    player->play();

    ui->pushButtonLiking->setEnabled(true);

    //添加到播放历史
    int index=playerList->currentIndex();
    QString currentName;
    for(QMap<QString,int>::iterator it=SongNameMap.begin();it!=SongNameMap.end();it++)
    {
        if(index==it.value())
        {
            currentName=it.key();
            break;
        }
    }
    for(QVector<QString>::iterator i=SongNameVector.begin();i!=SongNameVector.end();i++)
    {
        if(currentName==i)return;
    }
    QListWidgetItem *item=new QListWidgetItem(QIcon(":/source/haveplayed.png"),currentName);
    item->setToolTip(currentName);
    ui->listWidget_3->addItem(item);
    SongNameVector.push_back(currentName);
}

void Music::JugeLike()
{
    int index=playerList->currentIndex();
    //是否有喜欢标识
    if(IsLikedVector[index]==1)
    {
        ui->pushButtonLiking->setIcon(QIcon(":/source/loverded.png"));
        isAreadyLike=false;
    }
    else if(IsLikedVector[index]==2)
    {
        ui->pushButtonLiking->setIcon(QIcon(":/source/loverd.png"));
        isAreadyLike=true;
    }
}

void Music::on_pushButtonNextSong_clicked()   //下一首
{
    int index=playerList->currentIndex();
    if(playerList->playbackMode()==QMediaPlaylist::Random)
    {
        index=qrand()%playerList->mediaCount();
    }
    else
    {
        if(index==playerList->mediaCount()-1)
        {
            index=0;
        }
        else
        {
            index++;
        }
    }
    playerList->setCurrentIndex(index);
}

void Music::on_pushButtonLastSong_clicked()   //上一首
{
    int index=playerList->currentIndex();
    if(playerList->playbackMode()==QMediaPlaylist::Random)
    {
        index=qrand()%playerList->mediaCount();
    }
    else
    {
        if(index==0)
        {
            index=playerList->mediaCount()-1;
        }
        else
        {
            index--;
        }
    }
    playerList->setCurrentIndex(index);
}


void Music::on_pushButtonLiking_clicked()   //喜欢
{
    int TargetSong=0;
    int index=playerList->currentIndex();
    if(isAreadyLike)         //去掉喜欢
    {
        ui->pushButtonLiking->setIcon(QIcon(":/source/loverded.png"));
        isAreadyLike=false;

        for(QMap<QString,int>::iterator it=SongNameMap.begin();it!=SongNameMap.end();it++)   //从喜欢列表中删除
        {
            if(index==it.value())
            {
                for(int j=0;j<SameSongLike.size();j++)
                {
                    if(it.key()==SameSongLike[j])
                    {
                        ui->listWidget_2->takeItem(TargetSong);
                        IsLikedVector[index]=1;
                        for(int j=TargetSong;j<SameSongLike.size()-1;j++)
                        {
                            SameSongLike[j]=SameSongLike[j+1];
                        }
                        SameSongLike.pop_back();
                        return;
                    }
                    TargetSong++;
                }
            }
        }
    }
    else                   //添加喜欢
    {
        ui->pushButtonLiking->setIcon(QIcon(":/source/loverd.png"));
        isAreadyLike=true;

        //添加到喜欢列表
        QString currentName;
        for(QMap<QString,int>::iterator it=SongNameMap.begin();it!=SongNameMap.end();it++)
        {
            if(index==it.value())
            {
                currentName=it.key();
                break;
            }
        }
        for(QVector<QString>::iterator it=SameSongLike.begin();it!=SameSongLike.end();it++)
        {
            if(currentName==it)return;
        }
        QListWidgetItem *item=new QListWidgetItem(QIcon(":/source/loving.png"),currentName);
        item->setToolTip(currentName);
        ui->listWidget_2->addItem(item);
        SameSongLike.push_back(currentName);

        IsLikedVector[index]=2;
    }
}

void Music::on_pushButtonLoop_clicked()   //播放循环模式
{
    if(LoopIndex==1)
    {
        playerList->setPlaybackMode(QMediaPlaylist::Random);
        LoopIndex=2;
        ui->pushButtonLoop->setIcon(QIcon(":/source/random.png"));
        ui->pushButtonLoop->setToolTip(tr("随机播放"));
    }
    else if(LoopIndex==2)
    {
        playerList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        LoopIndex=3;
        ui->pushButtonLoop->setIcon(QIcon(":/source/loop.png"));
        ui->pushButtonLoop->setToolTip(tr("单曲循环"));
    }
    else if(LoopIndex==3)
    {
        playerList->setPlaybackMode(QMediaPlaylist::Loop);
        LoopIndex=1;
        ui->pushButtonLoop->setIcon(QIcon(":/source/playloop.png"));
        ui->pushButtonLoop->setToolTip(tr("顺序播放"));
    }
}

void Music::on_pushButtonVolum_clicked()   //音量
{
    if(!volumPressed)
    {
        ui->verticalSlider_2->show();
        volumPressed=true;
    }
    else
    {
        ui->verticalSlider_2->hide();
        volumPressed=false;
    }
}

void Music::setVolum()  //设置音量
{
    player->setVolume(ui->verticalSlider_2->value());
}

void Music::on_pushButtonAdd_clicked()   //添加音乐
{
    QString songName;
    QFileInfo info;
    QStringList SongPathList=QFileDialog::getOpenFileNames(this,"Add Songs","",tr("music(*.mp3)"));

    if(!SongPathList.empty())
    {
        for(int i=0;i<SongPathList.size();i++)
        {
            AddSongSame=false;   //歌曲不重复

            QString path=QDir::toNativeSeparators(SongPathList.at(i)); //获取歌曲文件地址
            songName=path.split("\\").last();   //获取歌名

            for(QMap<QString,int>::iterator it=SongNameMap.begin();it!=SongNameMap.end();it++)  //重复的则不添加
            {
                if(it.key()==songName)
                {
                    AddSongSame=true;
                }
            }

            if(AddSongSame==false)
            {
                playerList->addMedia(QUrl::fromLocalFile(path));   //向 “播放” 列表添加歌曲

                QListWidgetItem *item=new QListWidgetItem(QIcon(":/source/musics.png"),songName);  //添加项目信息
                item->setToolTip(songName);
                ui->listWidget->addItem(item);  //将项目添加到 ListWidget 歌曲列表中

                SongNameMap.insert(songName,SongNum); //保存歌名 序号
                SongNum++;   //列表中歌曲数
                IsLikedVector.push_back(1);   //初始化喜欢容器
                SongPathVector.push_back(path);  //存储歌曲路径
            }
        }
        ui->pushButtonSuspectSong->setEnabled(true);
        ui->pushButtonLastSong->setEnabled(true);
        ui->pushButtonNextSong->setEnabled(true);
    }
}

void Music::updateText()        //更新文本
{
    QString Text;
    if(player->isMetaDataAvailable())
    {
        QString Title=player->metaData(QStringLiteral("Title")).toString();
        if(!Title.isEmpty())
        {
            Text=Title;
        }
        else
        {
            Text+=("未知歌曲");
        }
        Text+="-";
        QString Author=player->metaData(QStringLiteral("Author")).toString();
        if(!Author.isEmpty())
        {
            Text+=Author;
        }
        else
        {
            Text+=("未知作者");
        }
    }
    ui->label->setText(Text);
    ui->labelSongName->setText(Text);
}

static QString Time(qint64 time)   //转换时间
{
    int sec=time/1000;
    int min=sec/60;
    sec-=min*60;
    return QStringLiteral("%1:%2")
            .arg(min, 2, 10, QLatin1Char('0'))
            .arg(sec, 2, 10, QLatin1Char('0'));
}

void Music::updatePosition(qint64 position)//更新位置
{
    if(BarInitPosition==0)   //歌词滑条初始位置
    {
        ui->textEdit->verticalScrollBar()->setValue(0);
        BarInitPosition=1;
    }

    ui->label_Time->setText(Time(position)+"/"+Time(player->duration()));

    ui->horizontalSlider->setValue(position);

    int currentPo;   //当前歌词滑条位置  时间
    currentPo= static_cast<int>(position);
    int TheLrcHeight=ui->textEdit->document()->size().height();  //歌词文本总高度
    for(QVector<LrcFormat>::iterator iter1=lrcVector.begin();iter1!=lrcVector.end();iter1++)
    {
        if(Time(position)==Time(iter1->ms))
        {
            if(currentPo!=0)
            {
                float SetBarPosition=(currentPo*TheLrcHeight/player->duration())-60;
                ui->textEdit->verticalScrollBar()->setValue(SetBarPosition);
            }
        }
    }
}

void Music::updateDuration(qint64 duration)//更新状态
{
    ui->horizontalSlider->setRange(0,duration);
    ui->horizontalSlider->setEnabled(duration>0);
    ui->horizontalSlider->setPageStep(duration/10);

    ui->textEdit->verticalScrollBar()->setRange(0,duration);
    ui->textEdit->verticalScrollBar()->setPageStep(duration/10);
}

void Music::on_horizontalSlider_valueChanged(int value)      //进度条拖动
{
    if(qAbs(value-player->position())>2000&&(ui->horizontalSlider->value()!=0))
    {
        player->stop();
        player->setPosition(value);
        if(isSuspect==false)
        {
            player->play();
        }
    }
}

void Music::lyrics()
{
    ui->textEdit->clear(); //清空歌词框
    ui->label_2->clear(); // 清空纯音乐标签
    lrcVector.clear(); //清空歌词容器

    int index=playerList->currentIndex();
    QString lrcPath = SongPathVector[index].mid(0, SongPathVector[index].lastIndexOf(".")) + QString(".lrc");  //歌词路径

    QFile file(lrcPath);
    if( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        QTextStream stream(&file);
        QString readStr = stream.readAll();

        QRegularExpression rex("\\[(\\d+)?:(\\d+\\.\\d+)?\\]"); // 正则表达式
        QRegularExpressionMatch match = rex.match(readStr);

        readStr = readStr.mid(match.capturedStart(), readStr.length() - match.capturedStart()); // 去掉 匹配到的第一个时间戳前的无用字符串
        //取指定截取字符串开始位置   取指定截取字符串指定截取长度

        if(readStr=="[00:00:00]此歌曲为没有填词的纯音乐，请您欣赏")
        {
            ui->label_2->setText("纯音乐，请欣赏");  //显示歌词
            ui->label_2->setAlignment(Qt::AlignCenter); //字体居中
            file.close();
            return;
        }

        while(true)
        {
            LrcFormat lrc;
            lrc.ms = static_cast<unsigned int>((match.captured(1).toInt() * 60000 + match.captured(2).toDouble() * 1000)); // 毫秒
            lrc.lrc = readStr.mid(match.capturedLength(), readStr.indexOf("\n") - match.capturedLength() + 1).simplified(); // 歌词
            readStr = readStr.mid(readStr.indexOf("\n") + 1, readStr.length() - readStr.indexOf("\n")); // 截取 已解析的字符串

            match = rex.match(readStr);
            lrcVector.append(lrc); // QVector<LrcFormat> 结构体容器

            if( readStr.indexOf("\n") < 0 ) // 结尾
            {
                LrcFormat end;
                end.ms = static_cast<unsigned int>((match.captured(1).toInt() * 60000 + match.captured(2).toDouble() * 1000));
                end.lrc = readStr.mid(match.capturedLength(), readStr.indexOf("\n") - match.capturedLength() + 1).simplified();
                lrcVector.append(end);
                break;
            }
        }

        file.close();
        for(QVector<LrcFormat>::iterator iter1=lrcVector.begin();iter1!=lrcVector.end();iter1++)
        {
            ui->textEdit->append(iter1->lrc);  //显示歌词
            ui->textEdit->setAlignment(Qt::AlignCenter); //字体居中
        }
    }

}







