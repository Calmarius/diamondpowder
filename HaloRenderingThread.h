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

        HaloRenderingSetupStruct &setupStruct;
};

#endif // HALO_RENDERING_THREAD_H
