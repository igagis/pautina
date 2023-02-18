/*
MIT License

Copyright (c) 2023 Ivan Gagis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ================ LICENSE END ================ */

#pragma once

#include <atomic>
#include <optional>

#include <nitki/thread.hpp>
#include <nitki/queue.hpp>
#include <opros/wait_set.hpp>

namespace nitki{

class loop_thread : public nitki::thread{
    nitki::queue queue;

    std::atomic_bool quit_flag = false;

public:
    opros::wait_set wait_set;

    loop_thread(unsigned wait_set_capacity);

    void run()override;

    /**
     * @brief Loop iteration procedure.
     * This function is called every main loop iteration, right after
     * handling thread's queue.
     * @param triggered - triggered waitable objects of wait_set.
     * @return desired triggering objects waiting timeout in milliseconds for next iteration.
     * @return empty std::optional for infinite waiting for triggering objects.
     */
    virtual std::optional<uint32_t> on_loop(utki::span<opros::event_info> triggered) = 0;

    /**
     * @brief Request this thread to quit.
     */
    void quit()noexcept;
};

}