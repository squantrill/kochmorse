#ifndef __KOCHMORSE_TRAINER_HH__
#define __KOCHMORSE_TRAINER_HH__

#include <QObject>
#include <QList>
#include <QVector>
#include <QSet>


/** Abstract base class of all tutor classes. */
class Tutor : public QObject
{
  Q_OBJECT

protected:
  /** Hidden constructor. */
  explicit Tutor(QObject *parent = 0);

public:
  /** Destructor. */
  virtual ~Tutor();

  /** Gets the next char from a session. */
  virtual QChar next() = 0;
  /** Returns true if the last char of a session has be taken. */
  virtual bool atEnd() = 0;
  /** Reset the tutor (start a new session). */
  virtual void reset() = 0;
};


/** A tutor for the Koch method. */
class KochTutor: public Tutor
{
  Q_OBJECT

public:
  /** Constructor.
   * @param lesson Specifies the lesson of the tutor [2, 43].
   * @param prefLastChars If @c true, specifies the if the symbols of the more recent lessons
   *        should be samples more likely by the tutor.
   * @param parent Specifies the QObject parent. */
  KochTutor(int lesson=2, bool prefLastChars=false, QObject *parent=0);
  /** Destructor. */
  virtual ~KochTutor();

  /** Samples the next character. */
  QChar next();
  /** If @ctrue, the current session is at the end. */
  bool atEnd();
  /** Reset/restarts a session. */
  void reset();

  /** Returns the current lesson. */
  int lesson() const;
  /** Sets the current lesson. */
  void setLesson(int lesson);
  /** Returns @c true if the symbols of the more resent lessons are sampled more likely. */
  bool prefLastChars() const;
  /** Enable preferred sampling of recent symbols. */
  void setPrefLastChars(bool pref);

protected:
  /** The current lesson. */
  int _lesson;
  /** The "prefer last chars" flag. */
  bool _prefLastChars;
  /** The list of chars of the current session. */
  QList<QChar> _text;
  /** The vector of symbols for each lesson. */
  static QVector<QChar> _lessons;
};


/** A simple tutor for random chars. */
class RandomTutor: public Tutor
{
  Q_OBJECT

public:
  /** Constructor. Uses all symbols for practicing. */
  explicit RandomTutor(QObject *parent=0);
  /** Constructor. Uses only the symbols specified by the @c chars set for practicing. */
  explicit RandomTutor(const QSet<QChar> &chars, QObject *parent=0);
  /** Destructor. */
  virtual ~RandomTutor();

  /** Samples the next symbol. */
  QChar next();
  /** If @ctrue, the current session is at the end. */
  bool atEnd();
  /** Reset/restarts a session. */
  void reset();

  /** Returns the set of characters to practice. */
  QSet<QChar> chars() const;
  /** Resets the set of characters to practice. */
  void setChars(const QSet<QChar> &chars);

protected:
  /** Text for the current session. */
  QList<QChar> _text;
  /** Vector of chars to choose from. */
  QVector<QChar> _chars;
};


/** A simple QSO tutor. */
class QSOTutor: public Tutor
{
  Q_OBJECT

public:
  explicit QSOTutor(QObject *parent=0);
  virtual ~QSOTutor();

  QChar next();
  bool atEnd();
  void reset();

protected:
  QVector<QString> _qso;
  QString _currentQSO;
};

#endif // __KOCHMORSE_TRAINER_HH__
