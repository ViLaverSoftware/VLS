/*
 * Copyright 2020 Vilaversoftware IVS (http://vilaversoftware.dk/)
 * Author: Mikkel N�hr L�vgreen (ml@vilaversoftware.dk)
 * ------------------------------------------------------------------------
 * Licensed to Vilaversoftware IVS who licenses this file to you under the
 * Apache License, Version 2.0 (the "License"); you may not use this file
 * except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <vector>
#include <memory>

namespace VLS::Event {

class Publisher;

/// <summary>
/// 
/// </summary>
class Subscriber {

public:
    using UPtr = std::unique_ptr<Subscriber>;

    /// <summary>
    /// 
    /// </summary>
    Subscriber(const Subscriber&) = delete;
    Subscriber() = default;

    virtual ~Subscriber();

    /// <summary>
    /// 
    /// </summary>
    void UnsubscribeAll();

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <return>  </return>
    bool Unsubscribe(Publisher& publisher);

    /// <summary>
    /// 
    /// </summary>
    /// <return>  </return>
    size_t PublisherCount() const;

private:
    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <return>  </return>
    bool _subscribe(Publisher* publisher);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="">  </param>
    /// <return>  </return>
    bool _unsubsribe(Publisher* publisher);

private:
    /// <summary>
    /// 
    /// </summary>
    std::vector<Publisher*> m_publishers;

    friend class Publisher;
};

}