/* @cpp.file.header */

/*  _________        _____ __________________        _____
 *  __  ____/___________(_)______  /__  ____/______ ____(_)_______
 *  _  / __  __  ___/__  / _  __  / _  / __  _  __ `/__  / __  __ \
 *  / /_/ /  _  /    _  /  / /_/ /  / /_/ /  / /_/ / _  /  _  / / /
 *  \____/   /_/     /_/   \_,__/   \____/   \__,_/  /_/   /_/ /_/
 */

#include "gridgain/impl/utils/gridclientdebug.hpp"

#include <sstream>
#include <stdexcept>

#include "gridgain/gridclientvariant.hpp"
#include "gridgain/gridclientnode.hpp"
#include "gridgain/impl/utils/gridutil.hpp"
#include "gridgain/impl/marshaller/gridnodemarshallerhelper.hpp"

using namespace std;

class GridClientNode::Impl {
public:
    /** Default constructor. */
    Impl() : replicaCount(-1), routerTcpAddress("",-1) {}

    /**
     * Copy costructor.
     *
     * @param other Node to copy data from.
     */
    Impl(const Impl& other) : nodeId(other.nodeId), tcpAddrs(other.tcpAddrs),
        metrics(other.metrics), attrs(other.attrs), routerTcpAddress(other.routerTcpAddress),
        dfltCacheMode(other.dfltCacheMode), caches(other.caches),
        replicaCount(other.replicaCount), consistentId(other.consistentId) {
    }

    /** Node ID */
    GridClientUuid nodeId;

    /** REST TCP addresses. */
    vector<GridClientSocketAddress> tcpAddrs;

    /** Metrics. */
    GridClientNodeMetricsBean metrics;

    /** Node attributes. */
    TGridClientVariantMap attrs;

    /** Mode for cache with {@code null} name. */
    string dfltCacheMode;

    /** Node caches. */
    TGridClientVariantMap caches;

    /** Router TCP address. */
    GridClientSocketAddress routerTcpAddress;

    /** Replicas count. */
    int replicaCount;

    /** Consistent ID. */
    GridClientVariant consistentId;
};

GridClientNode::GridClientNode(): pimpl(new Impl) {
}

GridClientNode::GridClientNode(const GridClientNode& other): pimpl(new Impl(*other.pimpl)){
}

GridClientNode& GridClientNode::operator=(const GridClientNode& rhs){
    if (this != &rhs) {
        delete pimpl;

        pimpl=new Impl(*rhs.pimpl);
    }

    return *this;
}

GridClientNode::~GridClientNode(){
    delete pimpl;
}

GridClientUuid GridClientNode::getNodeId() const {
    return pimpl->nodeId;
}

GridClientVariant GridClientNode::getConsistentId() const {
    return pimpl->consistentId;
}

const std::vector<GridClientSocketAddress> & GridClientNode::getTcpAddresses() const {
    return pimpl->tcpAddrs;
}

GridClientNodeMetricsBean GridClientNode::getMetrics() const {
    return pimpl->metrics;
}

TGridClientVariantMap GridClientNode::getAttributes() const {
    return pimpl->attrs;
}

TGridClientVariantMap GridClientNode::getCaches() const {
    return pimpl->caches;
}

std::string GridClientNode::getDefaultCacheMode() const {
    return pimpl->dfltCacheMode;
}

const GridClientSocketAddress & GridClientNode::getRouterTcpAddress() const {
    return pimpl->routerTcpAddress;

}

int GridClientNode::getReplicaCount() const {
    return pimpl->replicaCount;
}

std::ostream& operator<<(std::ostream &out, const GridClientNode &n){
    out << "GridClientNode [nodeId=" << n.getNodeId().uuid();
    out << ", tcpAddrs=";
    for (size_t i = 1; i < n.getTcpAddresses().size(); ++i) {
        if (i != 0)
            out << ",";

        out << n.getTcpAddresses()[i].host() << ":" << n.getTcpAddresses()[i].port();
    }

    out << ", routerTcpAddress=" << n.getRouterTcpAddress().host() << ":" << n.getRouterTcpAddress().port();

    out << ']';

    return out;
}

std::string GridClientNode::toString() const {
    std::ostringstream os;

    os << *this;

    return os.str();
}

void GridClientNodeMarshallerHelper::setNodeId(const GridClientUuid& pNodeId){
    node_.pimpl->nodeId = pNodeId;
}

void GridClientNodeMarshallerHelper::setTcpAddresses(std::vector<GridClientSocketAddress> & tcpAddrs) {
    node_.pimpl->tcpAddrs = tcpAddrs;
}

void GridClientNodeMarshallerHelper::setMetrics(const GridClientNodeMetricsBean& pMetrics) {
    node_.pimpl->metrics = pMetrics;
}

void GridClientNodeMarshallerHelper::setAttributes(const TGridClientVariantMap& pAttrs) {
    node_.pimpl->attrs = pAttrs;
}

void GridClientNodeMarshallerHelper::setCaches(const TGridClientVariantMap& pCaches) {
    node_.pimpl->caches = pCaches;
}

void GridClientNodeMarshallerHelper::setDefaultCacheMode(const string& pDfltCacheMode) {
    node_.pimpl->dfltCacheMode = pDfltCacheMode;
}

void GridClientNodeMarshallerHelper::setConsistentId(const GridClientVariant& pId) {
    node_.pimpl->consistentId = pId;
}

void GridClientNodeMarshallerHelper::setReplicaCount(int count) {
    node_.pimpl->replicaCount = count;
}

void GridClientNodeMarshallerHelper::setRouterTcpAddress(GridClientSocketAddress& routerAddress) {
    node_.pimpl->routerTcpAddress = routerAddress;
}

