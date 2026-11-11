/////////////////////////////////////////////////////////////////////////////
// eathread_lockfree.h
//
// Copyright (c) 2007, Electronic Arts Inc. All rights reserved.
//
// STATUS: BETA
// A version of this code has shipped on PS3. The implementation on other
// platforms involves significant new code, which has not been tested as
// extensively. 
// 
// Created by Stuart Riffle, EA Black Box
/////////////////////////////////////////////////////////////////////////////


#ifndef EATHREAD_EATHREAD_LOCKFREE_H
#define EATHREAD_EATHREAD_LOCKFREE_H

#ifndef INCLUDED_eabase_H
    #include <EABase/eabase.h>
#endif
#ifndef EATHREAD_EATHREAD_H
    #include <eathread/eathread.h>
#endif
#ifndef EATHREAD_EATHREAD_SYNC_H
    #include <eathread/eathread_sync.h>
#endif
#ifndef EATHREAD_EATHREAD_ATOMIC_H
    #include <eathread/eathread_atomic.h>
#endif
#ifndef EATHREAD_EATHREAD_ATOMICSTRUCT_H
    #include <eathread/eathread_atomicstruct.h>
#endif

#if defined(EA_PRAGMA_ONCE_SUPPORTED)
    #pragma once // Some compilers (e.g. VC++) benefit significantly from using this. We've measured 3-4% build speed improvements in apps as a result.
#endif



#if EATHREAD_ATOMICSTRUCTS_AVAILABLE

namespace EA
{
    namespace Thread
    {
        namespace LockFree
        {
            //-------------------------------------------------------------------------------------------
            /// Base class for items in lock-free containers
            /// 
            struct Node 
            {
                Node*       mNext;
            };


            //-------------------------------------------------------------------------------------------
            /// Simple lock-free queue
            /// 
            /// \author     Stuart Riffle (Black Box)
            /// \date       1/23/2008
            /// 
            class Queue
            {
                struct QueueInfo
                {
                    Node*   mHead;
                    Node*   mTail;
                };

                AtomicStruct< QueueInfo > mInfo;

            public:

                Queue() 
                {
                    ATOMIC_UPDATE_BEGIN( QueueInfo, &mInfo, info )
                    {
                        info->mHead = NULL;
                        info->mTail = NULL;
                    }
                    ATOMIC_UPDATE_END()
                }

                //-------------------------------------------------------------------------------------------
                /// Add a chain of nodes to the back of the queue
                /// 
                /// \param  first   First node in the chain
                /// \param  last    Last node in the chain
                ///
                /// The chain must be linked continuously from first to last, but last->mNext does not need
                /// to be initialized. It is fine for both first and last to point to the same node.
                /// 
                void PushBackChain( Node* first, Node* last )
                {
                    Node* tailPrev = NULL;

                    // Terminate the linked list at the last node.

                    WriteSyncUintptr( &last->mNext, NULL );

                    // Install the last node as the tail link in the list (and if the list is currently
                    // empty, install the first node as the head link).

                    ATOMIC_UPDATE_BEGIN( QueueInfo, &mInfo, info )
                    {
                        tailPrev    = info->mTail;
                        info->mTail = last;
                        info->mHead = info->mHead? info->mHead : first;
                    }
                    ATOMIC_UPDATE_END()

                    // At this point:
                    // 
                    // -    Because tailPrev->mNext is NULL, the new nodes are unreachable by someone
                    //      walking from the front of the queue.
                    // -    Because tailPrev->mNext is NULL, but it is no longer the last link in the
                    //      list (mTail != tailPrev), it will not be popped from the queue, because
                    //      PopFront() will recognize that it's unlinked.
                    // -    It is our responsibility to link tailPrev to our new nodes, but there is no
                    //      race to do so. We could even do it asynchronously as a fire-and-forget write,
                    //      as long as the caller understands that the new nodes they just pushed
                    //      will not be immediately poppable.
                    // -    It is safe for asynchronous calls to modify mTail. It will be *their*
                    //      responsibility to link last->mNext to whatever they are appending.
                    //
                    // So complete the chain...

                    if( tailPrev != NULL )
                        WriteSyncUintptr( &tailPrev->mNext, (uintptr_t) first );
                }

                //-------------------------------------------------------------------------------------------
                /// Add a single node to the back of the queue
                /// 
                /// \param  node    Node to add
                ///
                void PushBack( Node* node )
                {
                    this->PushBackChain( node, node );
                }

                //-------------------------------------------------------------------------------------------
                /// Remove a single node from the front of the queue
                /// 
                /// \return     The first node in the queue, or NULL if the queue is empty
                ///
                Node* PopFront()
                {
                    Node* node = NULL;

                    ATOMIC_UPDATE_BEGIN( QueueInfo, &mInfo, info )
                    {
                        if( info->mHead != info->mTail )
                        {
                            // More than one node in the list

                            node = info->mHead;
                            info->mHead = (Node*) ReadSyncUintptr( &node->mNext );

                            // Bail if the head node isn't linked yet

                            if( info->mHead == NULL )
                                return( NULL );
                        }
                        else
                        {
                            // Bail if the list is empty

                            if( info->mHead == NULL )
                                return( NULL );

                            // Exactly one node in the list

                            node = info->mHead;
                            info->mHead = NULL;
                            info->mTail = NULL;
                        }
                    }
                    ATOMIC_UPDATE_END()

                    return( node );
                }
            };


            //-------------------------------------------------------------------------------------------
            /// Simple lock-free stack
            /// 
            /// \author     Stuart Riffle (Black Box)
            /// \date       1/23/2008
            /// 
            class Stack
            {
                struct StackInfo
                {
                    Node*   mHead;
                };

                AtomicStruct< StackInfo > mInfo;

            public:

                Stack()
                {
                    ATOMIC_UPDATE_BEGIN( StackInfo, &mInfo, info )
                    {
                        info->mHead = NULL;
                    }
                    ATOMIC_UPDATE_END()
                }

                //-------------------------------------------------------------------------------------------
                /// Add a single node to the top of the stack
                /// 
                /// \param  node    Node to add
                ///
                void Push( Node* node )
                {
                    ATOMIC_UPDATE_BEGIN( StackInfo, &mInfo, info )
                    {
                        WriteSyncUintptr( &node->mNext, (uintptr_t) info->mHead );
                        info->mHead = node;
                    }
                    ATOMIC_UPDATE_END()
                }

                //-------------------------------------------------------------------------------------------
                /// Remove a single node from the top of the stack
                /// 
                /// \return     The top node, or NULL if the stack is empty
                ///
                Node* Pop()
                {
                    Node* node = NULL;

                    ATOMIC_UPDATE_BEGIN( StackInfo, &mInfo, info )
                    {
                        node = info->mHead;
                        if( node == NULL )
                            break;

                        info->mHead = (Node*) ReadSyncUintptr( &node->mNext );
                    }
                    ATOMIC_UPDATE_END()

                    return( node );
                }
            };


        } // namespace LockFree
    } // namespace Thread
} // namespace EA

#endif // EATHREAD_ATOMICSTRUCTS_AVAILABLE

#endif // Header include guard

