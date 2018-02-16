type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string
};

let cache = ApolloInMemoryCache.createInMemoryCache(~dataIdFromObject=(obj: dataObject) => obj##id, ());

let link = ApolloLinks.createHttpLink(~uri="/graphql", ());

module Client =
  ReasonApollo.CreateClient(
    {
      let apolloClient = ReasonApollo.createApolloClient(~cache, ~link, ());
    }
  );
