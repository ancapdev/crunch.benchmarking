#ifndef CRUNCH_CONCURRENCY_META_SCHEDULER_HPP
#define CRUNCH_CONCURRENCY_META_SCHEDULER_HPP

#include "crunch/concurrency/scheduler.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/thread/mutex.hpp>

#include <vector>

namespace Crunch { namespace Concurrency {

// Very simple scheduler to run multiple cooperative schedulers. E.g.,
// - task scheduler
// - io_service scheduler
// - fiber / coroutine scheduler
class MetaScheduler
{
public:
    typedef boost::shared_ptr<IScheduler> SchedulerPtr;
    typedef std::vector<SchedulerPtr> SchedulerList;

    MetaScheduler(SchedulerList const& schedulers);

    // Run the scheduler on this thread.
    // TODO: mask for which types of schedulers to run? or simply have multiple meta schedulers for that purpose?
    // - Could have a two way affinity mask, one for the scheduler and one for the thread. If their conjunction is non-zero run the scheduler
    // - Should maybe notify a scheduler that it is not running on a particular thread. E.g., to orphan work to other threads immediately.
    void Run();

    // Interrupt all threads running the scheduler
    void InterruptAll();

    // Interrupt the current thread's scheduler.
    void InterruptCurrent();

private:
    SchedulerList mSchedulers;
    boost::mutex mSchedulersLock;
};

}}

#endif