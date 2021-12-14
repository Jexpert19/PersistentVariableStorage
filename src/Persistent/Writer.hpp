#pragma once/*
#include "Position.hpp"
#include "Searcher.hpp"

namespace Persistent{
    class Writer{
        private:
        Base* storageBase;
        Position* position;
        Searcher* searcher;

        public:
        Writer(Base& storageBase,
               Position& position,
               Searcher& searcher)
        :storageBase{&storageBase}, position{&position}, searcher{&searcher}{}

        // Get's set in this function
        // - Sentinel
        // - Checksum
        void writeToNextWritableBlock(Block& block){
            block.head.sentinel = position->getSentinelWriteValue();
            goToNextWritableBlock(block.head);
            storageBase->write(&block, position->getWritePosition(), sizeof(Block));
            position->toNextBlock();
        }

        private:
        void goToNextWritableBlock(Block::Head& targetHead){
            while(!blockIsWritable(targetHead)){
            updateCurrentBlocksSentinel();
            position->toNextBlock();
            }
        }

        void updateCurrentBlocksSentinel(){
            Block::Head head;
            storageBase->read(&head, position->getWritePosition(), Block::HEADSIZE);

            head.sentinel = position->getSentinelWriteValue();

            storageBase->write(&head, position->getWritePosition(), Block::HEADSIZE);
        }

        bool blockIsWritable(Block::Head& targetHead){
            Block::Head head;
            storageBase->read(&head, position->getWritePosition(), Block::HEADSIZE);

            // Could be overwritten or updated
            if(targetHead.key == head.key ||
            head.deleted == true){
            return true;
            }

            uint16_t latest_occurance;
            if(searcher->findLatest(&head, &latest_occurance) != Error::ok){
            // TODO: ERROR
            }

            // Don't overwrite up to date data
            if(latest_occurance == position->getWritePosition()){
                return false;
            }

            return true;
        }
    };
}*/