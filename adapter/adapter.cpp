/**
 * 适配器模式
 *
 * 将一个类的接口转换成客户希望的另一个接口，使得原本由于接口不兼容而不能一起工作的哪些类可以一起工作。
 *
 * 主要解决：主要解决在软件系统中，常常要将一些"现存的对象"放到新的环境中，而新环境要求的接口是现对象不能满足的。
 * 何时使用：
 *      1、系统需要使用现有的类，而此类的接口不符合系统的需要。
 *      2、想要建立一个可以重复使用的类，用于与一些彼此之间没有太大关联的一些类，包括一些可能在将来引进的类一起工作，这些源类不一定有一致的接口。
 *      3、通过接口转换，将一个类插入另一个类系中。（比如老虎和飞禽，现在多了一个飞虎，在不增加实体的需求下，增加一个适配器，在里面包容一个虎对象，实现飞的接口。）
 * 如何解决：继承或依赖（推荐）。
 * 关键代码：适配器继承或依赖已有的对象，实现想要的目标接口。
 * 缺点：1、过多地使用适配器，会让系统非常零乱，不易整体进行把握。比如，明明看到调用的是 A 接口，其实内部被适配成了 B 接口的实现，一个系统如果太多出现这种情况，无异于一场灾难。因此如果不是很有必要，可以不使用适配器，而是直接对系统进行重构。
*/

#include <iostream>
#include <memory>

class MediaPlayer {
public:
    virtual void play(std::string audioType, std::string fileName) = 0;

    virtual ~MediaPlayer() = default;
};

class AdvancedMediaPlayer {
public:
    virtual void playVlc(std::string fileName) = 0;
    virtual void playMp4(std::string fileName) = 0;

    virtual ~AdvancedMediaPlayer() = default;
};

class VlcPlayer: public AdvancedMediaPlayer {
public:
    virtual void playVlc(std::string fileName) override {
        std::cout << "Playing vlc file. Name: " << fileName << std::endl;
    }

    virtual void playMp4(std::string fileName) override {}
};

class Mp4Player: public AdvancedMediaPlayer {
public:
    virtual void playVlc(std::string fileName) override {}

    virtual void playMp4(std::string fileName) override {
        std::cout << "Playing mp4 file. Name: " << fileName << std::endl;
    }
};

class MediaAdapter: public MediaPlayer {
public:
    MediaAdapter(std::string audioType) {
        if (audioType == "vlc") {
            advancedMusicPlayer = std::shared_ptr<VlcPlayer>(new VlcPlayer());
        } else if (audioType == "mp4") {
            advancedMusicPlayer = std::shared_ptr<Mp4Player>(new Mp4Player());
        }
    }

    void play(std::string audioType, std::string fileName) {
        if (audioType == "vlc") {
            advancedMusicPlayer->playVlc(fileName);
        } else if (audioType == "mp4") {
            advancedMusicPlayer->playMp4(fileName);
        }
    }

private:
    std::shared_ptr<AdvancedMediaPlayer> advancedMusicPlayer;
};

class AudioPlayer: public MediaPlayer {
public:
    virtual void play(std::string audioType, std::string fileName) override {
        //播放 mp3 音乐文件的内置支持
        if (audioType == "mp3") {
            std::cout << "Playing mp3 file. Name: " << fileName << std::endl;
        } else if (audioType == "vlc"
                   || audioType == "mp4") { //mediaAdapter 提供了播放其他文件格式的支持
            mediaAdapter = std::shared_ptr<MediaAdapter>(new MediaAdapter(audioType));
            mediaAdapter->play(audioType, fileName);
        } else {
            std::cout << "Invalid media. " << audioType << " format not supported" << std::endl;
        }
    }
private:
    std::shared_ptr<MediaAdapter> mediaAdapter;
};

int main() {
    std::shared_ptr<AudioPlayer> audioPlayer(new AudioPlayer());
    audioPlayer->play("mp3", "beyond the horizon.mp3");
    audioPlayer->play("mp4", "alone.mp4");
    audioPlayer->play("vlc", "far far away.vlc");
    audioPlayer->play("avi", "mind me.avi");

    return 0;
}