/*
 * TiSceneManager.h
 *
 *  Created on: Jul 25, 2013
 *      Author: penrique
 */

#ifndef TI_TISCENEMANAGER_H_
#define TI_TISCENEMANAGER_H_

#include <QList>

namespace bb
{
namespace cascades
{
class AbstractPane;
}
}

namespace Ti
{
class TiSceneManager {
public:
	TiSceneManager();
	virtual ~TiSceneManager();
	void addPane(bb::cascades::AbstractPane*);
	void removePane(bb::cascades::AbstractPane*);
	static TiSceneManager* Instance();
	static void Open(bb::cascades::AbstractPane*);
	static void Close(bb::cascades::AbstractPane*);
private:
	QList<bb::cascades::AbstractPane*> _scenes;
};
}
#endif /* TISCENEMANAGER_H_ */
