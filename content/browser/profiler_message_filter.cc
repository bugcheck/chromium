// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/browser/profiler_message_filter.h"

#include "base/tracked_objects.h"
#include "content/browser/profiler_controller_impl.h"
#include "content/common/child_process_messages.h"

namespace content {

ProfilerMessageFilter::ProfilerMessageFilter(ProcessType process_type)
    : process_type_(process_type) {
}

ProfilerMessageFilter::~ProfilerMessageFilter() {
}

void ProfilerMessageFilter::OnChannelConnected(int32 peer_pid) {
  BrowserMessageFilter::OnChannelConnected(peer_pid);

  tracked_objects::ThreadData::Status status =
      tracked_objects::ThreadData::status();
  Send(new ChildProcessMsg_SetProfilerStatus(status));
}

bool ProfilerMessageFilter::OnMessageReceived(const IPC::Message& message,
                                              bool* message_was_ok) {
  bool handled = true;
  IPC_BEGIN_MESSAGE_MAP_EX(ProfilerMessageFilter, message, *message_was_ok)
    IPC_MESSAGE_HANDLER(ChildProcessHostMsg_ChildProfilerData,
                        OnChildProfilerData)
    IPC_MESSAGE_UNHANDLED(handled = false)
  IPC_END_MESSAGE_MAP_EX()
  return handled;
}

void ProfilerMessageFilter::OnChildProfilerData(
    int sequence_number,
    const tracked_objects::ProcessDataSnapshot& profiler_data) {
  ProfilerControllerImpl::GetInstance()->OnProfilerDataCollected(
      sequence_number, profiler_data, process_type_);
}

}
