#ifndef __OutputObject_h__
#define __OutputObject_h__

#include <maya/MStatus.h>
#include <maya/MFloatArray.h>
#include <maya/MFloatPointArray.h>
#include <maya/MVectorArray.h>
#include <maya/MStringArray.h>
#include <maya/MIntArray.h>
#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>

#include <HAPI/HAPI.h>

class Asset;

class OutputObject {

    public:
        enum ObjectType {
            OBJECT_TYPE_GEOMETRY,
            OBJECT_TYPE_INSTANCER
        };

        // static creator
        static OutputObject* createObject(
                int assetId,
                int objectId,
                const HAPI_ObjectInfo &objectInfo
                );

        OutputObject(
                int assetId,
                int objectId
              );
        virtual ~OutputObject();

        int getId();
        MString getName();

        void setObjectInfo(const HAPI_ObjectInfo &objectInfo);

        //virtual MStatus compute(const MPlug& plug, MDataBlock& data);
        virtual MStatus compute(
                const MTime &time,
                MDataBlock& data,
                MDataHandle& handle,
                bool &needToSyncOutputs
                ) = 0;

        virtual ObjectType type() = 0;

        bool        isVisible() const;
        bool        isInstanced() const;

    public:
        bool myIsInstanced;

    protected:
        HAPI_ObjectInfo myObjectInfo;
        int myAssetId;
        int myObjectId;

        bool myNeverBuilt;
};

#endif
