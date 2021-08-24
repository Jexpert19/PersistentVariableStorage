#pragma once
#include "PersistentStorageBase.hpp"
#include "PersistentStoragePosition.hpp"
#include "PersistentStorageSearcher.hpp"

namespace PersistentStorage{
    template<size_t BLOCK_SIZE>
    class PersistentStorageWriter{
        private:
        PersistentStorageBase<BLOCK_SIZE>* storageBase;
        PersistentStoragePosition<BLOCK_SIZE>* position;
        PersistentStorageSearcher<BLOCK_SIZE>* searcher;

        public:
        PersistentStorageWriter(PersistentStorageBase<BLOCK_SIZE>* storageBase,
                                PersistentStoragePosition<BLOCK_SIZE>* position,
                                PersistentStorageSearcher<BLOCK_SIZE>* searcher)
        :storageBase{storageBase}, position{position}, searcher{searcher}{}

        // Get's set in this function
        // - Sentinel
        // - Checksum
        void writeToNextWritableBlock(PersistentBlock<BLOCK_SIZE>& block){
            block->head.sentinel = position->getSentinelWriteValue();
            goToNextWritableBlock(&block->head);
            storageBase->writeBlock(position->getWritePosition(), block);
            position->toNextBlock();
        }

        private:
        void goToNextWritableBlock(PersistentBlockHead& targetHead){
            while(!blockIsWritable(targetHead)){
            updateCurrentBlocksSentinel();
            position->toNextBlock();
        }
        }

        void updateCurrentBlocksSentinel(){
            PersistentBlockHead head;
            storageBase->get_head(position->get_write_position(), &head);

            head.sentinel = position->getSentinelWriteValue();

            storageBase->writeHead(position->get_write_position(), &head);
        }

        bool blockIsWritable(PersistentBlockHead& targetHead){
            PersistentBlockHead head;
            storageBase->get_head(position->get_write_position(), &head);

            // Could be overwritten or updated
            if(targetHead.key == head.key ||
            head.overwritable == true){
            return true;
            }

            persistentAddress_t latest_occurance;
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
    }