#ifndef ACCOUNTRESPONSE_H
#define ACCOUNTRESPONSE_H
#include "response.h"
#include "../asset.h"
#include "../assettypenative.h"
#include "link.h"
#include <QMetaProperty>
#include <QVariantMap>
namespace AccountResponseAttach
{
/**
 * Represents account thresholds.
 */
class Thresholds {
    Q_GADGET
    Q_PROPERTY(int low_threshold MEMBER m_lowThreshold)
    Q_PROPERTY(int med_threshold MEMBER m_medThreshold)
    Q_PROPERTY(int high_threshold MEMBER m_highThreshold)

    int m_lowThreshold;
    int m_medThreshold;
    int m_highThreshold;
public:
    Thresholds();

    int getLowThreshold();
    int getMedThreshold();
    int getHighThreshold();
    bool operator !=(Thresholds& t);
};

/**
 * Represents account flags.
 */
class Flags {
    Q_GADGET
    Q_PROPERTY(bool auth_required MEMBER m_authRequired)
    Q_PROPERTY(bool auth_revocable MEMBER m_authRevocable)
    bool m_authRequired;
    bool m_authRevocable;
public:
    Flags();

    bool getAuthRequired();
    bool getAuthRevocable();
    bool operator !=(Flags& f);
};

/**
 * Represents account balance.
 */
class Balance {
    Q_GADGET
    Q_PROPERTY(QString asset_type MEMBER m_assetType)
    Q_PROPERTY(QString asset_code MEMBER m_assetCode)
    Q_PROPERTY(QString asset_issuer MEMBER m_assetIssuer)
    Q_PROPERTY(QString limit MEMBER m_limit)
    Q_PROPERTY(QString balance MEMBER m_balance)

    QString m_assetType;
    QString m_assetCode;
    QString m_assetIssuer;
    QString m_limit;
    QString m_balance;

    KeyPair *m_assetIssuerKeypair;
    Asset *m_asset;
public:
    Balance();
    ~Balance();
    Asset* getAsset();
    QString getAssetType();
    QString getAssetCode();
    QString assetIssuer();
    KeyPair& getAssetIssuer();
    QString getBalance();
    QString getLimit();
    bool operator !=(Balance& b);
    bool operator ==(Balance& b);

};

/**
 * Represents account signers.
 */
class Signer {
    Q_GADGET
    Q_PROPERTY(QString public_key MEMBER m_accountId )
    Q_PROPERTY(QString key MEMBER m_accountId )
    Q_PROPERTY(QString type MEMBER m_type )
    Q_PROPERTY(int weight MEMBER m_weight)

    QString m_accountId;
    QString m_type;
    int m_weight;

public:
    Signer();

    //use getKey() instead
    Q_DECL_DEPRECATED QString getAccountId() const;
    QString getKey() const;
    QString getType() const;

    int getWeight() const;

    bool operator !=(Signer& s);
    bool operator ==(Signer& s);
};

/**
 * Links connected to account.
 */
class Links {
    Q_GADGET
    Q_PROPERTY(Link effects MEMBER m_effects)
    Q_PROPERTY(Link offers MEMBER m_offers)
    Q_PROPERTY(Link operations MEMBER m_operations)
    Q_PROPERTY(Link self MEMBER m_self)
    Q_PROPERTY(Link transactions MEMBER m_transactions)

    Link m_effects;
    Link m_offers;
    Link m_operations;
    Link m_self;
    Link m_transactions;
public:

    Link getEffects();
    Link getOffers();
    Link getOperations();
    Link getSelf();
    Link getTransactions();
    bool operator !=(Links& links);
};
}


class AccountResponse : public Response
{
    Q_OBJECT
    Q_PROPERTY(QString account_id READ accountID WRITE setAccountID)
    Q_PROPERTY(KeyPair* keypair READ getKeypair)//we dont allow to overwrite this
    Q_PROPERTY(qint64 sequence MEMBER m_sequence NOTIFY sequenceNumberChanged)
    Q_PROPERTY(QString paging_token MEMBER m_pagingToken NOTIFY pagingTokenChanged)
    Q_PROPERTY(int subentry_count MEMBER m_subentryCount NOTIFY subentryCountChanged)
    Q_PROPERTY(QString inflation_destination MEMBER m_inflationDestination NOTIFY inflationDestinationChanged)
    Q_PROPERTY(QString home_domain MEMBER m_homeDomain NOTIFY homeDomainChanged)
    Q_PROPERTY(AccountResponseAttach::Thresholds thresholds MEMBER m_thresholds NOTIFY thresholdsChanged)
    Q_PROPERTY(AccountResponseAttach::Flags flags MEMBER m_flags NOTIFY flagsChanged)
    Q_PROPERTY(QList<AccountResponseAttach::Balance> balances MEMBER m_balances NOTIFY balancesChanged)
    Q_PROPERTY(QList<AccountResponseAttach::Signer> signers MEMBER m_signers NOTIFY signersChanged)
    Q_PROPERTY(AccountResponseAttach::Links _links MEMBER m_links NOTIFY linksChanged)
    QString m_account_id;
    KeyPair * m_keypair;//generated with m_account_id

    qint64 m_sequence;
    QString m_pagingToken;
    int m_subentryCount;
    QString m_inflationDestination;
    QString m_homeDomain;
    AccountResponseAttach::Thresholds m_thresholds;
    AccountResponseAttach::Flags m_flags;
    QList<AccountResponseAttach::Balance> m_balances;
    QList<AccountResponseAttach::Signer> m_signers;
    AccountResponseAttach::Links m_links;

public:
    Q_INVOKABLE explicit AccountResponse(QNetworkReply* reply=nullptr);
    virtual ~AccountResponse();

    // TransactionBuilderAccount interface
public:
    /**
     * @brief getKeypair
     * @return KeyPair* , it will get deleted when AccountResponse get deleted.
     */
    KeyPair *getKeypair();
    qint64 getSequenceNumber() const;
    qint64 getIncrementedSequenceNumber() const;
    void incrementSequenceNumber();
    QString accountID() const;
    AccountResponseAttach::Links getLinks() const;
    QString getPagingToken() const;
    qint64 getSubentryCount() const;
    QString getInflationDestination() const;
    QString getHomeDomain() const;
    AccountResponseAttach::Thresholds getThresholds() const;
    AccountResponseAttach::Flags getFlags() const;
    QList<AccountResponseAttach::Balance> getBalances() const;
    QList<AccountResponseAttach::Signer> getSigners() const;

public slots:
    void setAccountID(QString account_id);
signals:
    void sequenceNumberChanged();
    void pagingTokenChanged();
    void subentryCountChanged();
    void inflationDestinationChanged();
    void homeDomainChanged();
    void thresholdsChanged();
    void flagsChanged();
    void balancesChanged();
    void signersChanged();
    void linksChanged();

};

Q_DECLARE_METATYPE(AccountResponseAttach::Thresholds)
Q_DECLARE_METATYPE(AccountResponseAttach::Flags)
Q_DECLARE_METATYPE(AccountResponseAttach::Balance)
Q_DECLARE_METATYPE(AccountResponseAttach::Signer)
Q_DECLARE_METATYPE(AccountResponseAttach::Links)

#endif // ACCOUNTRESPONSE_H
