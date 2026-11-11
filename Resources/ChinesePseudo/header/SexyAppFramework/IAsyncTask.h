#ifndef IASYNC_TASK_H_INCLUDED
#define IASYNC_TASK_H_INCLUDED

namespace Sexy
{
	class IAsyncTask
	{
	public:
		virtual ~IAsyncTask() {};

		virtual bool IsDone() = 0;
		virtual bool HasError() = 0;

		virtual void Destroy() = 0;
	};
};

#endif
