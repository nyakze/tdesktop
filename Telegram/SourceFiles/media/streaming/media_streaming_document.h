/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "media/streaming/media_streaming_player.h"
#include "ui/effects/radial_animation.h"
#include "ui/effects/animations.h"
#include "base/timer.h"

class DocumentData;

namespace Media {
namespace Streaming {

class Instance;

class Document {
public:
	Document(
		not_null<DocumentData*> document,
		std::shared_ptr<Reader> reader);

	void play(const PlaybackOptions &options);
	void saveFrameToCover();

	[[nodiscard]] Player &player();
	[[nodiscard]] const Player &player() const;
	[[nodiscard]] const Information &info() const;

	[[nodiscard]] bool waitingShown() const;
	[[nodiscard]] float64 waitingOpacity() const;
	[[nodiscard]] Ui::RadialState waitingState() const;

private:
	friend class Instance;

	void registerInstance(not_null<Instance*> instance);
	void unregisterInstance(not_null<Instance*> instance);

	void waitingCallback();

	void handleUpdate(Update &&update);
	void handleError(Error &&error);

	void ready(Information &&info);
	void waitingChange(bool waiting);

	void validateGoodThumbnail();

	Player _player;
	Information _info;

	bool _waiting = false;
	mutable Ui::InfiniteRadialAnimation _radial;
	Ui::Animations::Simple _fading;
	base::Timer _timer;
	base::flat_set<not_null<Instance*>> _instances;

	not_null<DocumentData*> _document;

};


} // namespace Streaming
} // namespace Media