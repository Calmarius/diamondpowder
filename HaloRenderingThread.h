/*
Copyright (c) 2012, Dávid Csirmaz
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file HaloRenderingThread.h
 *
 * A tread the renders the halo display.
 */

#ifndef HALO_RENDERING_THREAD_H
#define HALO_RENDERING_THREAD_H

BEGIN_DECLARE_EVENT_TYPES()
    DECLARE_LOCAL_EVENT_TYPE(wxEVT_HALO_RENDERING_THREAD_NOTIFY, -1)
END_DECLARE_EVENT_TYPES()

class HaloRenderingThread : public wxThread
{
    public:
        HaloRenderingThread(HaloRenderingSetupStruct &setupStruct) : wxThread(wxTHREAD_JOINABLE), setupStruct(setupStruct)
        {
        }
        /**
         * Executes the thread. It will send wxCommandEvents
         */
        virtual ExitCode Entry();
    private:

        Matrix getOrientationMatrix(CrystalDescriptor::OrientationType orientation);
        void sendNotifyString(const wxString &str, int terminate = 0);
/*        void createCrystals();
        void bucketCrystals();
        void renderDisplay();*/
        static void freeBuffer(uint32_t *ptr);
        static void freeMap(std::map<RayPathId, RayPathDescriptor> *ptr);

        HaloRenderingSetupStruct &setupStruct; ///< Input and output stored in it.
};

#endif // HALO_RENDERING_THREAD_H
