#include <iostream>
#include <string>
using namespace std;

class MediaFile {
public:
	virtual void play() = 0;
	virtual void pause() = 0;
	virtual void stop() = 0;
	virtual void displayDetails() = 0;
};

class AudioFile : public MediaFile 
{
	string artistName;
	int duration;
	int volume;
	int currentPosition;

public:
	AudioFile(string artistName, int duration) 
	{
		this->artistName = artistName;
		this->duration = duration;
		this->volume = 50;
		this->currentPosition = 0;
	}

	void play()
	{
		cout << "Playing audio file" << endl;
	}
	void pause()
	{
		cout << "Pausing audio file" << endl;
	}
	void stop()
	{
		cout << "Stopping audio file" << endl;
	}
	void adjustVolume(int newVolume) 
	{
		volume = newVolume;
	}
	void displayCurrentPosition() 
	{
		cout << "Current position  : " << currentPosition << " seconds" << endl;
	}
	void displayDetails() {
		cout << "Artist     : " << artistName << endl;
		cout << "Duration   : " << duration << " seconds" << endl;
		cout << "Volume     : " << volume << endl;
	}
};

class VideoFile : public MediaFile 
{
	string resolution;
	int duration;
	int brightness;
	int contrast;
	int currentPosition;

public:
	VideoFile(string resolution, int duration) 
	{
		this->resolution = resolution;
		this->duration = duration;
		this->brightness = 50;
		this->contrast = 50;
		this->currentPosition = 0;
	}

	void play()
	{
		cout << "Playing video file" << endl;
	}
	void pause()
	{
		cout << "Pausing video file" << endl;
	}
	void stop()
	{
		cout << "Stopping video file" << endl;
	}
	void adjustBrightness(int newBrightness) 
	{
		brightness = newBrightness;
	}
	void adjustContrast(int newContrast) 
	{
		contrast = newContrast;
	}
	void displayCurrentPosition() 
	{
		cout << "Current position  : " << currentPosition << " seconds" << endl;
	}
	void displayDetails() 
	{
		cout << "Resolution  : " << resolution << endl;
		cout << "Duration    : " << duration << " seconds" << endl;
		cout << "Brightness  : " << brightness << endl;
		cout << "Contrast    : " << contrast << endl;
	}
};

class MediaLibrary 
{
	MediaFile** mediaFiles;
	int capacity;
	int numFiles;

public:
	MediaLibrary(int capacity) 
	{
		this->capacity = capacity;
		this->numFiles = 0;
		this->mediaFiles = new MediaFile * [capacity];
	}
	~MediaLibrary() {
		for (int i = 0; i < numFiles; i++) {
			delete mediaFiles[i];
		}
		delete[] mediaFiles;
	}
	void addMediaFile(MediaFile* file) {
		if (numFiles < capacity) {
			mediaFiles[numFiles] = file;
			numFiles++;
		}
		else {
			cout << "Media library is full" << endl;
		}
	}
	void playMediaFile(int index)
	{
		if (index >= 0 && index < numFiles)
		{
			mediaFiles[index]->play();

			int choice = 1;
			while (choice != 0) 
			{
				cout << "1. Pause" << endl;
				cout << "2. Stop" << endl;
				cout << "3. Play" << endl;
				cout << "0. Back to Main Menu" << endl;
				cout << "Enter your choice : ";
				cin >> choice;

				switch (choice) {
				case 1:
					mediaFiles[index]->pause();
					break;
				case 2:
					mediaFiles[index]->stop();
					break;
				case 3:
					mediaFiles[index]->play();
					break;

				}

				cout << endl;
				system("pause");
				system("cls");
			}
		}
		else
		{
			cout << "Invalid index" << endl;
		}
	}

	void displayMediaFileDetails() 
	{
		for (int i = 0; i < numFiles; i++) {
			cout << "Media file " << i << " : ";
			mediaFiles[i]->displayDetails();
			cout << endl;
		}
	}
};

int main() {
	MediaLibrary library(10);

	int choice = 1;
	while (choice != 0) 
	{
		cout << "1. Add Audio File" << endl;
		cout << "2. Add Video File" << endl;
		cout << "3. Play Media File" << endl;
		cout << "4. Display Media File Details" << endl;
		cout << "0. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) 
		{
		case 1: 
		{
			string artistName;
			int duration;
			cout << "Enter artist name  : ";
			cin.ignore();
			getline(cin, artistName);
			cout << "Enter duration     : ";
			cin >> duration;

			AudioFile* audioFile = new AudioFile(artistName, duration);
			library.addMediaFile(audioFile);

			cout << "Audio file added to the library" << endl;
			break;
		}
		case 2: 
		{
			string resolution;
			int duration;
			cout << "Enter video resolution  : ";
			cin.ignore();
			getline(cin, resolution);
			cout << "Enter duration          : ";
			cin >> duration;

			VideoFile* videoFile = new VideoFile(resolution, duration);
			library.addMediaFile(videoFile);

			cout << "Video file added to the library" << endl;
			break;
		}
		case 3: 
		{
			int index;
			cout << "Enter the index of the media file to play  : ";
			cin >> index;

			library.playMediaFile(index);
			break;
		}
		case 4:
			library.displayMediaFileDetails();
			break;
		}
		system("pause");
		system("cls");
		cout << endl;
	}

	return 0;
}
