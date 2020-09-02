#ifndef MUSIC_H
#define MUSIC_H

#include <QDialog>
#include<QMouseEvent>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QFileDialog>
#include<QListWidget>
#include<QListWidgetItem>
#include<QList>
#include<QMap>
#include<QSlider>
#include<QScrollBar>
#include<QTime>
#include<QLabel>
#include<QTimer>
#include<QTime>
#include<QtMath>

namespace Ui {
class Music;
}

typedef struct _tLrcFormat
{
    unsigned int ms;
    QString lrc;
} LrcFormat;


class Music : public QDialog
{
    Q_OBJECT

public:
    explicit Music(QWidget *parent = nullptr);


    bool eventFilter(QObject* object, QEvent* event);

    ~Music();

private slots:

    void LrcPageChange();   //歌词页面改变
    void lrcTimeStart();   //绘制歌词图片

    void on_pushButtonDestroy_clicked();   //关闭窗口

    void on_pushButtonMIN_clicked();   //最小化

    void on_pushButtonTheme_clicked();   //主题

    void on_pushButtonSuspectSong_clicked();   //暂停

    void on_pushButtonNextSong_clicked();  //下一首

    void on_pushButtonLastSong_clicked();  //上一首

    void on_pushButtonAdd_clicked();  //添加歌曲


    void DoubleClicked(QListWidgetItem *);//双击播放

    void updatePosition(qint64 position);  //更新位置
    void updateDuration(qint64 duration);//更新状态
    void updateText();        //更新文本

    void on_pushButtonLoop_clicked();  //循环模式

    void on_pushButtonVolum_clicked();  //音量
    void setVolum();   //处理音量

    void JugeLike();  //是否喜欢

    void on_horizontalSlider_valueChanged(int value); //进度条拖动

    void LrcPhotoChange();    //歌词图片改变

    void on_pushButtonLiking_clicked();

    void on_pushButtonHome_clicked();

    void on_pushButtonLike_clicked();

    void on_pushButtonUsed_clicked();

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleseEvent(QMouseEvent *);

    int angle=0;   //旋转角度
    QPixmap pix;  //歌词页面
    QTimer *timer;
    QString LrcPhoto=":/source/911.png";   //初始化歌词图

    bool mouseIsPressd;   //鼠标是否被按下
    QPoint mousePosition;  //鼠标位置

    bool AddSongSame=false;  //添加重复歌曲
    int SongNum=0;  //歌曲序号
    bool isSuspect=true;  //是否暂停
    int ThemeNum=1;    //主题序号
    int LoopIndex=1;   //循环模式编号
    bool volumPressed=false;  //音量键未被按下
    bool isAreadyLike=false;   //是否喜欢

    int BarInitPosition=0;

    QMediaPlayer *player;    //播放器
    QMediaPlaylist *playerList;  //播放列表

    QMap<QString,int>SongNameMap; //存储列表 歌名+序号
    QVector<QString>SongPathVector;   //歌曲路径
    QVector<QString>SongNameVector;  //防止同名
    QVector<int>IsLikedVector;   //是否喜爱
    QVector<QString>SameSongLike;   //我的喜爱歌名防止同名

    QVector<LrcFormat>lrcVector;  //歌词

    void lyrics();   //歌词函数

    void DealPlayer();   //处理双击事件 暂停图标

    Ui::Music *ui;
};

#endif // MUSIC_H
